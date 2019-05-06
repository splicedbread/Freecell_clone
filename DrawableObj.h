#ifndef DRAWABLEOBJ_H
#define DRAWABLEOBJ_H
/*/////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 5/4/19
	File: DrawableObj.h
	Purpose: class for defining an object
		with dimensions and some sort of image.
		complete with pointers to a parent object
		and a group
*//////////////////////////////////////////////////
class DrawableObj
{
	friend class GroupObj;
public:
	DrawableObj();
	DrawableObj(const char * name);
	DrawableObj(const char * name, int width, int height);
	~DrawableObj();
	
	DrawableObj & operator=(const DrawableObj & rhs);


	void SetName(const char * name);
	void SetSrc(const char * src);
	void SetGroup(const char * group);

	void SetDims(int x, int y); //size in pixels
	void SetPos(int x, int y); //using top left as origin

	const char * GetName() const;
	const char * GetSrc() const;
	const char * GetGroup() const;
	
	int GetWidth() const;
	int GetHeight() const;
	int GetXpos() const;
	int GetYpos() const;

private:
	char * m_name;
	char * m_src_path;
	char * m_group;

	int m_width;
	int m_height;

	int m_Xpos_rel; //relative positioning
	int m_Ypos_rel;
};
#endif // !DRAWABLEOBJ_H