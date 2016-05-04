#include "stdafx.hpp"
#include "main.h"

#include <math.h>
#include <time.h>
#include <Windows.h>

#include "event_receiver.hpp"
#include "fighet_scene_node.hpp"
#include "enemie_scene_node.hpp"
#include "enemie_scene_node_manager.hpp"
#include "rocket_scene_node.hpp"
#include "rocket_mamager.hpp"
#include "explosion/CMain.h"
#include "c_timer.hpp"
#include "IrrKlang_include/irrKlang.h"

#include "gui/main_menu.h"

using namespace irr;
using namespace irrklang;

MyEventReceiver* Global::myEventReceiver = nullptr;
video::IVideoDriver* Global::spVideoDriver = nullptr;

int main ()
{
	// Main device //
	IrrlichtDevice * pMainDevice = createDevice ( video::EDT_OPENGL
		, core::dimension2d < u32 > ( X_SIDE, Y_SIDE ), 16, false, false, false );
	if ( ! pMainDevice )
		return EXIT_FAILURE;

	// Main audio device //
	ISoundEngine * pSoundEngine = createIrrKlangDevice ();
	if ( ! pSoundEngine )
		return EXIT_FAILURE;

	// Initializing application context structure //
	sApplicationContext context;
	context.m_pMainDevice = pMainDevice;
	context.m_counter = 0;
	context.isInGame = false;

	// Initializing receiver //
	Global::myEventReceiver = new MyEventReceiver(&context);

	pMainDevice->setEventReceiver ( Global::myEventReceiver ); // Adding receiver to device
	pMainDevice->setWindowCaption ( L"Space Battle" ); // Text on the top of the application 
	pMainDevice->setResizable ( false ); // Disabling window resizing

	// Getting all main controll componets //
	// Static part //
	Global::spVideoDriver = pMainDevice->getVideoDriver ();

	// Other part // 
	scene::ISceneManager * pSceneManager = pMainDevice->getSceneManager ();
	scene::ICameraSceneNode * pCamera = pSceneManager->addCameraSceneNode ();
	gui::IGUIEnvironment * pGUIEnvironment = pMainDevice->getGUIEnvironment();

	// Vector for controling all animators //
	std::vector < scene::ISceneNodeAnimator * > pAnimators; 

	// Setting the main menu audio //
	//pSoundEngine->play2D ( "audio\\ophelia.mp3", true );

	// Random number for choosing an enemie texture //
	srand ( time ( NULL ) );

	// Camera positioning and targeting //
	pCamera->setPosition ( core::vector3df ( 0, 0, 200 ) );
	pCamera->setTarget ( core::vector3df ( 0, 0, 0 ) );

	//////////////////////////////
	f32 fov = pCamera->getFOV ();

	leftBorder = pCamera->getPosition ().Z * tan ( fov / 2 );

	rightBorder = - leftBorder;
	//////////////////////////////

	// Background cube //
	scene::IMeshSceneNode * pCube 
		= pSceneManager->addCubeSceneNode ( 1, nullptr, -1, core::vector3df ( 0, 0, -15 ) );

	pCube->setScale ( core::vector3df ( X_SIDE / 2, Y_SIDE / 2, 0.1f ) );
	pCube->setMaterialFlag ( video::EMF_LIGHTING, false );

	video::ITexture * pTexture = Global::spVideoDriver->getTexture ( "export\\background.tga" );

	pCube->setMaterialTexture ( 0, pTexture );

	// Border for rockets //
		// for fighter
	scene::IMeshSceneNode * pWorldBorder = pSceneManager->addCubeSceneNode ( X_SIDE, nullptr, -1,
		irr::core::vector3df ( 0, 220, 0 ), 
		irr::core::vector3df ( 0, 0, 0 ),
		irr::core::vector3df ( X_SIDE, 0.001f, 2 ) );

		// For enemies
	scene::IMeshSceneNode * pWorldBorderEnemieRockets = pSceneManager->addCubeSceneNode ( X_SIDE
		, nullptr, -1
		, irr::core::vector3df ( 0, -220, 0 )
		, irr::core::vector3df ( 0, 0, 0 )
		, irr::core::vector3df ( X_SIDE, 0.001f, 2 ) );

	// Rockets manager set //
		// for fighter rockets
	cRocketManager rockets ( pSceneManager, pMainDevice, "export\\rocket.X", pWorldBorder );

		// for enemies rockets
	cRocketManager enemieRockets ( pSceneManager, pMainDevice, "export\\rocket.X"
		, pWorldBorderEnemieRockets, false );

	// Fighter set //
	cFighterSceneNode * pFighter = new cFighterSceneNode ( pSceneManager, "export\\fighter.X", 
			3, MOVEMENT_SPEED,
			core::vector3df ( 0, downBorder, 0 ), // Position
			core::vector3df ( 0, 180, 0 ), // Rotation
			core::vector3df ( 1.0f, 1.0f, 1.0f ) ); // Scale
	
	pFighter->setTexture ( "export\\fighter.tga", Global::spVideoDriver );

	// Enemie set //
	cEnemieNodeManager enemieManager ( pMainDevice );

	enemieManager.addEnemieType ( "export\\enemies_01" );
	enemieManager.addEnemieType ( "export\\enemies_02" );
	enemieManager.addEnemieType ( "export\\enemies_03" );
	enemieManager.addEnemieType ( "export\\enemies_04" );

	// For statisctic. Font, billboard text //
	gui::IGUIFont * pFont = pGUIEnvironment->getFont ( "export\\fonthaettenschweiler.bmp" ); 

	scene::IBillboardTextSceneNode * pTextVictory = pSceneManager->addBillboardTextSceneNode ( pFont
		, L"You won!"
		, nullptr, core::dimension2df ( 100, 10 ), core::vector3df ( 0, 40, 10 ) );
	scene::IBillboardTextSceneNode * pTextToExit = pSceneManager->addBillboardTextSceneNode ( pFont
		, L"Press ESCAPE to exit"
		, nullptr, core::dimension2df ( 100, 10 ), core::vector3df ( 0, -20, 10 ) );
	scene::IBillboardTextSceneNode * pTextEnemiesKilled = pSceneManager->addBillboardTextSceneNode ( pFont
		, L"temp"
		, nullptr, core::dimension2df ( 100, 10 ), core::vector3df ( 0, 20, 10 ) );
	scene::IBillboardTextSceneNode * pTextRocketsLaunched = pSceneManager->addBillboardTextSceneNode ( pFont
		, L"temp"
		, nullptr, core::dimension2df ( 100, 10 ), core::vector3df ( 0, 0, 10 ) );

	pTextVictory->setVisible ( false );
	pTextToExit->setVisible ( false );
	pTextEnemiesKilled->setVisible ( false );
	pTextRocketsLaunched->setVisible ( false );

	// Createing the main menu //
	MainMenu* mainMenu = new MainMenu(pGUIEnvironment);

	// Before the main loop starts //
	bool isPressed = false; 
	bool isLaunched = false; // for rocket
	bool isEnemieRocketLauched = false; // for enemie rockets
	bool isEnd = false;	// For drawing stats
	bool isThrusterSoundActive = false;

	unsigned int currentSelectedGameLevel = 0;
	bool isLevelFinished = false;
	bool isEnemiesCreated = false; // Cheking  if enemies creation, to avoid multiple creation of enemies group
	
	int rocketsCount = 0;
	int rocketsArraySize = rockets.getArraySize();
	wchar_t buf [25];

	cTimer timer ( pMainDevice );

	// Prepearing sound source //
	ISound * pSoundThruster = nullptr;

	enemieRockets.cleareRocketsAnimators ();
	enemieRockets.addAnimatorsToRockets ( pFighter, pWorldBorderEnemieRockets );

	/////////////// Main loop ///////////////
	while ( pMainDevice->run () )
	{
		//if ( pMainDevice->isWindowActive () )
		{
			if ( context.isInGame ) // is game started
			{
#if !defined(_DEBUG)
				// Start playing the thrusters sound //
				if ( ! isThrusterSoundActive )
				{
					pSoundThruster = nullptr;

					pSoundThruster = pSoundEngine->play2D ( "audio\\140582__lg__a320-engines-running-111228.wav"
						, true, false, true );

					isThrusterSoundActive = true;
				}
#endif
				
				isEnemiesCreated = (currentSelectedGameLevel == context.currentLevel) && !isLevelFinished;
				if ( ! isEnemiesCreated && ! isEnd )
				{
					enemieManager.clearEnemiesVector ();

					setEnemiesFleeet ( & pAnimators, & enemieManager, pSceneManager, &context );

					rockets.cleareRocketsAnimators ();
					rockets.addAnimatorsToRockets ( & enemieManager, pWorldBorder );

					currentSelectedGameLevel = context.currentLevel;
					isLevelFinished = false;
				}

				// Cheking if victory and showing stats
				if ( enemieManager.getVectorSize () == 0 )
				{
					rockets.reload ();
					if ( ! isEnd )
					{
						isEnd = true;
						isLevelFinished = true;

						pTextVictory->setText ( L"You won!!!" );

						pTextToExit->setText ( L"Press ESCAPE to exit" );

						// enemie killed count
						swprintf ( buf, 20, L"Enemies killed: %d"
							, enemieManager.getNEnemiesKilled () );
						
						pTextEnemiesKilled->setText ( buf );
						
						* buf = '\0'; // String clear

						// rockets launched count
						swprintf ( buf, 25, L"Rockrets launched: %d"
							, pFighter->getNRocketsLaunched () );

						pTextRocketsLaunched->setText ( buf );

						* buf = '\0'; // String clear

						enemieManager.reloadNEnemiesKilled ();
						pFighter->reloadNRocketsLaunched ();

						pTextVictory->setVisible ( true );
						pTextToExit->setVisible ( true );
						pTextEnemiesKilled->setVisible ( true );
						pTextRocketsLaunched->setVisible ( true );
					}
				}
				
				// If exiting make all invisible //
				if ( Global::myEventReceiver->IsKeyDown ( irr::KEY_ESCAPE ) && isEnd )
				{
					context.isInGame = false;
					isLevelFinished = true;
					isEnd = false;

					pTextVictory->setText ( L"" );
					pTextToExit->setText ( L"" );
					pTextEnemiesKilled->setText ( L"" );
					pTextRocketsLaunched->setText ( L"" );

					pTextVictory->setVisible ( false );
					pTextToExit->setVisible ( false );
					pTextEnemiesKilled->setVisible ( false );
					pTextRocketsLaunched->setVisible ( false );
						
					pFighter->getMeshSceneNode ()->setPosition ( core::vector3df ( 0, downBorder, 0 ) );

					for ( int i = 0; i < rockets.getArraySize (); i++ )
						rockets.getRockets()->at ( i )->getMeshSceneNode ()->setPosition ( 
							core::vector3df ( 0, upBorder + 100, 0 ) );

					// Pausing thrusters sound //
					if(pSoundThruster)
					{
						pSoundThruster->stop ();

						pSoundThruster->drop ();
						pSoundThruster = nullptr;
					}

					isThrusterSoundActive = false;
					
					continue;
				}

				if ( Global::myEventReceiver->IsKeyDown ( irr::KEY_ESCAPE ) && ! isEnd )
				{
					context.isInGame = false;

#if !defined(_DEBUG)
					// Pausing thrusters sound //
					pSoundThruster->stop ();

					pSoundThruster->drop ();
					pSoundThruster = nullptr;

					isThrusterSoundActive = false;
#endif
				}

				float currentSpeed = pFighter->getSpeed (); // getting the cuurrent speed of the fighter
		
				// Ghange!!!
				core::vector3df nodePosition = pFighter->getMeshSceneNode ()->getPosition (); // getting fighter position

				// Side movement //
				if ( ! isEnd )
				{
					float deltaTime = (f32)timer.getDeltaTime() / 100;
					if (   Global::myEventReceiver->IsKeyDown(irr::KEY_KEY_A)
						|| Global::myEventReceiver->IsKeyDown(irr::KEY_LEFT) )
					{
						nodePosition.X += currentSpeed * deltaTime;
					}

					if (   Global::myEventReceiver->IsKeyDown(irr::KEY_KEY_D)
						|| Global::myEventReceiver->IsKeyDown(irr::KEY_RIGHT))
					{
						nodePosition.X -= currentSpeed * deltaTime;
					}
		
					if ( nodePosition.X < leftBorder && nodePosition.X > rightBorder )
						pFighter->getMeshSceneNode ()->setPosition ( nodePosition );

					// Collison cheking //
					int animatorCount = collisionChek ( & rockets );

					if (!(animatorCount == -1 || animatorCount == 0 ))
					{
						enemieManager.increaseNEnemiesKilled ();

						core::vector3df collisionPosition = enemieManager.getEnemie ( animatorCount - 1 )->
							getMeshSceneNode ()->getPosition  ();

						addExplosion ( collisionPosition, core::vector3df ( 0, 0, 0 )
							, 10, pSceneManager, core::plane3df ( 1, 0, 0, 0, 0, 0 ), nullptr );

						pSoundEngine->play2D ( "audio\\explosion.flac", false );

						enemieManager.getEnemie ( animatorCount - 1 )->getMeshSceneNode ()->setVisible ( false );
						enemieManager.getEnemie ( animatorCount - 1 )->drop ();
						enemieManager.getVector()->erase ( enemieManager.getVector ()->begin () + animatorCount - 1 );

						rockets.cleareRocketsAnimators ();
						rockets.addAnimatorsToRockets ( & enemieManager, pWorldBorder );
					}

					animatorCount = collisionChek ( & enemieRockets );

					if (!( animatorCount == 0 || animatorCount == -1 ))
					{
						addExplosion ( pFighter->getMeshSceneNode()->getPosition () 
							, core::vector3df ( 0, 0, 0 ), 10
							, pSceneManager, core::plane3df ( 1, 0, 0, 0, 0, 0 ), nullptr );

						pSoundEngine->play2D ( "audio\\explosion.flac", false );

						pTextVictory->setText ( L"You Lose!!!" );
					
						isEnd = true;
						isEnemiesCreated = true;

						// enemie killed count
						swprintf ( buf, 20, L"Enemies killed: %d"
							, enemieManager.getNEnemiesKilled () );
						
						pTextEnemiesKilled->setText ( buf );
						
						* buf = '\0'; // String clear

						// rockets launched count
						swprintf ( buf, 25, L"Rockrets launched: %d"
							, pFighter->getNRocketsLaunched () );

						pTextRocketsLaunched->setText ( buf );

						* buf = '\0'; // String clear

						enemieManager.reloadNEnemiesKilled ();
						pFighter->reloadNRocketsLaunched ();

						pTextToExit->setText ( L"Press ESCAPE to exit" );

						pTextVictory->setVisible ( true );
						pTextToExit->setVisible ( true );
						pTextEnemiesKilled->setVisible ( true );
						pTextRocketsLaunched->setVisible ( true );
					}

					// Fire //
					if ( Global::myEventReceiver->IsKeyDown ( irr::KEY_SPACE ) && ! isLaunched )
					{
						isLaunched = true;

						printf ( "Fighter: rocket %d launched on %f, %f, %f\n", 
							rocketsCount++,
							pFighter->getMeshSceneNode()->getPosition ().X,
							pFighter->getMeshSceneNode()->getPosition ().Y,
							pFighter->getMeshSceneNode()->getPosition ().Z );

						pFighter->launch ( & rockets, Global::spVideoDriver );

						pSoundEngine->play2D ( "audio\\rocket_launch.mp3" );
					}
					else if ( ! Global::myEventReceiver->IsKeyDown ( irr::KEY_SPACE ) && isLaunched ) 
						isLaunched = false;

					/*if ( myEventReceiver->IsKeyDown ( irr::KEY_SPACE ) && ! isLaunched )
					{
						isLaunched = true;

						printf ( "Fighter: rocket %d launched on %f, %f, %f\n", 
							rocketsCount++,
							pFighter->getMeshSceneNode()->getPosition ().X,
							pFighter->getMeshSceneNode()->getPosition ().Y,
							pFighter->getMeshSceneNode()->getPosition ().Z );

						pFighter->launch ( & rockets, pVideoDriver );
					}
					else if ( ! myEventReceiver->IsKeyDown ( irr::KEY_SPACE ) && isLaunched ) 
						isLaunched = false;*/

					if ( rockets.getUsed () == rocketsArraySize )
					{
						rockets.reload ();
						//rocketsCount = 0;
					}

					if ( timer.calculateDeltaTime () > 1000 && enemieManager.getVectorSize () != 0 )
					{
						/*if ( myEventReceiver->IsKeyDown ( irr::KEY_KEY_Q ) )
							printf ( "DEBUG: debugin stop\n" );*/

						timer.calculateTime ();

						int i = rand () % enemieManager.getVectorSize (); // misstake

						enemieManager.getEnemie ( i )->launch ( & enemieRockets, Global::spVideoDriver );
					}
					else if ( enemieManager.getVectorSize () == 0 )
						printf ( "DEBUG: vector size = %d\n", enemieManager.getVectorSize () );
				}

			} // is game started
		
			// DEBUG //
			if ( Global::myEventReceiver->IsKeyDown ( irr::KEY_KEY_G ) && ! isPressed )
			{
				isPressed = true;
				printf ( "DEBUG: Fighter position - %f\n", pFighter->getMeshSceneNode()->getPosition().X );
			}
			if ( ! Global::myEventReceiver->IsKeyDown ( irr::KEY_KEY_G ) && isPressed )
				isPressed = false;
							
			// Drawing //
			Global::spVideoDriver->beginScene ( true, true, video::SColor ( 0, 255, 255, 255 ) );

			if ( context.isInGame )
			{
				pSceneManager->drawAll ();
			}
			else
			{
				pGUIEnvironment->drawAll ();
			}

			// Drawing stoped //
			Global::spVideoDriver->endScene ();
		}
	}	/////////////// Main loop ///////////////

	delete mainMenu;

	// Clrearing //
	pFighter->drop ();
	pSoundEngine->drop ();
	pMainDevice->drop ();
	/// ------- ///

	return EXIT_SUCCESS;
}

int collisionChek ( cRocketManager * _pRockets, bool isGood )
{
	int nRockets = _pRockets->getArraySize ();

	for ( int i = 0; i < nRockets; i++ )
	{
		if ( _pRockets->getRockets()->at ( i )->isLaunched () )
		{
			std::vector< irr::scene::ISceneNodeAnimatorCollisionResponse * >::iterator it = _pRockets->getRockets()->at ( i )->getAnimators()->begin();

			int index = 0;

			while ( it != _pRockets->getRockets()->at ( i )->getAnimators()->end () )
			{
				if ( ( * it )->collisionOccurred () )
				{
					if ( isGood )
						_pRockets->getRockets ()->at ( i )->getMeshSceneNode ()->
							setPosition ( irr::core::vector3df ( 0, UP_BORDER + 100, 0 ) );
					else 
						_pRockets->getRockets ()->at ( i )->getMeshSceneNode ()->
							setPosition ( irr::core::vector3df ( 0, DOWN_BORDER - 100, 0 ) );

					std::vector< irr::scene::ISceneNodeAnimatorCollisionResponse * >::iterator tempIt = _pRockets->getRockets()->at ( i )->getAnimators()->begin ();

					while ( tempIt != _pRockets->getRockets()->at ( i )->getAnimators()->end () )
					{
						( * tempIt )->setGravity ( NO_GRAVITY );
						tempIt++;
					}

					return index;
				}

				index++;
				it++;
			}
		}
	}

	return -1;
}

void setEnemiesFleeet(std::vector < scene::ISceneNodeAnimator * > * _pAnimators,
					  cEnemieNodeManager * _pEnemieManager,
					  scene::ISceneManager * _pSceneMager, 
					  sApplicationContext * _pContext)
{
	// Creating enemies
	unsigned int enemiesCount = 0;
	switch(_pContext->currentLevel)
	{
	case GUI_ID_CHOOSE_LEVEL_1: enemiesCount = GAME_LEVEL_1_ENEMIES_COUNT; break;
	case GUI_ID_CHOOSE_LEVEL_2: enemiesCount = GAME_LEVEL_2_ENEMIES_COUNT; break;
	case GUI_ID_CHOOSE_LEVEL_3: enemiesCount = GAME_LEVEL_3_ENEMIES_COUNT; break;
	case GUI_ID_CHOOSE_LEVEL_4: enemiesCount = GAME_LEVEL_4_ENEMIES_COUNT; break;
	}

	_pAnimators->clear();

	for ( int i = 0; i < enemiesCount; i++ )
		_pEnemieManager->newEnemie ();

	// Animator for the enemie // 
	int j = 0;
	const int enemiesInRow = 8;

	while ( enemiesCount / enemiesInRow >= j )
	{
		int i = 0;

		while ( i < enemiesInRow && enemiesInRow * j + i < enemiesCount )
		{
			core::vector3df startPosition = core::vector3df(leftBorder - i * 45 - 50,
															upBorder - j * 45, 
															0);
			
			core::vector3df endPosition = core::vector3df(rightBorder + 45 * enemiesInRow - i * 45,
														  upBorder - j * 45, 
														  0);

			_pAnimators->push_back ( _pSceneMager->createFlyStraightAnimator (
				startPosition, // start position 
				endPosition, // finish position
				1000, true, true ) );

			if ( ( * _pAnimators )[enemiesInRow * j + i] )
			{
				_pEnemieManager->getEnemie ( enemiesInRow * j + i  )->getMeshSceneNode ()->addAnimator ( 
					( * _pAnimators )[enemiesInRow * j + i] );

				( * _pAnimators )[enemiesInRow * j + i]->drop ();
			}

			scene::ITriangleSelector * pSelector = _pSceneMager->createOctreeTriangleSelector ( 
				_pEnemieManager->getEnemie ( enemiesInRow * j + i )->getMesh ()
				, _pEnemieManager->getEnemie ( enemiesInRow * j + i )->getMeshSceneNode (), 128 );

			_pEnemieManager->getEnemie ( enemiesInRow * j + i )->getMeshSceneNode ()
				->setTriangleSelector ( pSelector );

			++i;
		}

		++j;
	}
}