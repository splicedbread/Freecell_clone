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
	DrawableObj(const char * name, float scale);
	DrawableObj(const DrawableObj & cpy);
	~DrawableObj();
	
	DrawableObj & operator=(const DrawableObj & rhs);
	bool operator==(const DrawableObj & rhs);
	bool operator!=(const DrawableObj & rhs);


	void SetName(const char * name);
	void SetSrc(const char * src);
	void SetGroup(const char * group);

	void SetScale(float scale); //scale
	void SetPos(int x, int y); //using top left as origin

	const char * GetName() const;
	const char * GetSrc() const;
	const char * GetGroup() const;
	
	float GetScale() const;
	int GetXpos() const;
	int GetYpos() const;

private:
	char * m_name;
	char * m_src_path;
	char * m_group;

	float m_scale;

	int m_Xpos_rel; //relative positioning
	int m_Ypos_rel;
};
#endif // !DRAWABLEOBJ_H