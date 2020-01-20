#ifndef PLANET_H
#define PLANET_H
#include "vec3.h"
#include "gltexture.h"
class planet
{
public:
  float aroundRotatedSpeed;//��ת
  float selfRotatedSpeed;//��ת
  float radius;//���ǵİ뾶��Ӱ����ƵĴ�С��
  //���������������ǰ�����븸��֮��ĵľ�����
  //1.̫��ϵ��̫��Ϊ���Ľ����˶�
  //2.���������������������̫��������ת�͹�ת����˶�������������˵��̫�����Ǹ��ף��������Ǿ��Ƕ���
  //3�Ƚ�������ǵ��򣬵���Ҳ�����̫��������ת�͹�ת�ģ����ǵ�����һ�����ӣ���������˶���������˵�����ĸ����ǵ������ĸ��׵ĸ�����̫��
  //��ι�ϵ�ܽ����£�
  //   ̫��
  //      ����������������������
  //      ����
  //         ����
  vec3 pos;
 
  glTexture *texture;
public:
 
  planet(const char* texname,float as,float ss,float radius,vec3 pos)
  {
    texture=new glTexture(texname,true);
    this->aroundRotatedSpeed =as;
    this->selfRotatedSpeed =ss;
    this->radius =radius;
    this->pos =pos;
   
  }

  ~planet()
  {
	  if (!texture)
	  {
		  delete texture;
		  texture = NULL;
	  }
  }

};
#endif