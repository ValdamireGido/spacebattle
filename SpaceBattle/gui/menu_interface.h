#ifndef _MENU_ITERFACE_H_
#define _MENU_ITERFACE_H_

class MenuInterface
{
public:
	MenuInterface(irr::gui::IGUIEnvironment* environment);
	~MenuInterface();

	virtual void Init() {}

protected:
	void _LoadBackground(const std::string& path);
	
protected:
	irr::gui::IGUIEnvironment* m_env;

private:
	irr::gui::IGUIImage* m_background;
};

#endif // _MENU_ITERFACE_H_