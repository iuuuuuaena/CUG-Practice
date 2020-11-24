// 33.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "assert.h"
#include <iostream>
#include "scene_parser.h"
#include "image.h"
#include "ray.h"
#include "Camera.h"
#include "OrthographicCamera.h"
#include "hit.h"
#include "Group.h"
#include "light.h"
#include "ArcParse.h"

int main(int argc, char **argv)
{
	ArcParse *ap = new ArcParse(argc, argv);
	Image img(ap->width, ap->height);
	Image img_depth(ap->width, ap->height);
	Image img_normal(ap->width, ap->height);
	SceneParser *sp = new SceneParser(ap->input_file);
	Camera *camera = sp->getCamera();
	Group *group = sp->getGroup();
	img.SetAllPixels(sp->getBackgroundColor());
	img_depth.SetAllPixels(Vec3f(0,0,0));
	img_normal.SetAllPixels(Vec3f(0, 0, 0));
	int num_light = sp->getNumLights();
	for (size_t i = 0; i < ap->width; i++)
	{
		for (size_t j = 0; j < ap->height; j++)
		{
			Vec2f p((float)i / (float)ap->width, (float)j / (float)ap->height);
			Ray r = camera->generateRay(p);
			Hit h(INT_MAX, NULL,Vec3f(0,0,0));
			float tmin = camera->getTMin();
			//float tmp = 0;
			if (group->intersect(r, h, tmin))
			{
				Vec3f normal = h.getNormal();
				if (ap->shade_back)
				{
					if (normal.Dot3(r.getDirection()))
					{
						normal = -1.f*normal;//光线方向和法向量的点积为正数时，需要翻转法向量
					}
				}
				Vec3f color = sp->getAmbientLight();
				if (normal.Dot3(r.getDirection()))
				{
					for (size_t k = 0; k < num_light; k++)
					{
						Light *light = sp->getLight(k);
						Vec3f p = r.pointAtParameter(h.getT());//交点
						Vec3f dir, col;
						light->getIllumination(p, dir, col);
						float d = dir.Dot3(normal);
						d = d < 0 ? 0 : d;		//d = L.N if L.N > 0   = 0	其它
						color += d * col;
					}
					img.SetPixel(i, j, color*h.getMaterial()->getDiffuseColor());
					float t = h.getT();
					//tmp = t;
					if (t <= ap->depth_max && t >= ap->depth_min)
					{
						t = (t - ap->depth_min) / (ap->depth_max - ap->depth_min);
						t = 1.f - t;
						img_depth.SetPixel(i, j, Vec3f(t, t, t));
					}
					img_normal.SetPixel(i, j, normal);
				}
				
			}
			//printf("%f ", tmp);
		}
		//printf("\n");
	}
	if (ap->output_file!=NULL)
	{
		img.SaveTGA(ap->output_file);
	}
	if (ap->depth_file!=NULL)
	{
		img_depth.SaveTGA(ap->depth_file);
	}
	if (ap->normal_file!=NULL)
	{
		img_normal.SaveTGA(ap->normal_file);
	}
}
