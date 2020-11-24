// 32.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
#include "ArcParse.h"

int main(int argc,char **argv)
{
	ArcParse *ap = new ArcParse(argc, argv);
	Image img(ap->width, ap->height);
	Image img_depth(ap->width, ap->height);
	SceneParser *sp = new SceneParser(ap->input_file);
	Camera *camera = sp->getCamera();
	Group *group = sp->getGroup();
	img.SetAllPixels(sp->getBackgroundColor());
	img_depth.SetAllPixels(sp->getBackgroundColor());
	for (size_t i = 0; i < ap->width; i++)
	{
		for (size_t j = 0; j < ap->height; j++)
		{
			Vec2f p((float)i / (float)ap->width, (float)j / (float)ap->height);
			Ray r = camera->generateRay(p);
			Hit h(INT_MAX, NULL);
			float tmin = camera->getTMin();
			//float tmp = 0;
			if (group->intersect(r,h,tmin))
			{
				img.SetPixel(i, j, h.getMaterial()->getDiffuseColor());
				float t = h.getT();
				//tmp = t;
				if (t<=ap->depth_max&&t>=ap->depth_min)
				{
					t = (t - ap->depth_min) / (ap->depth_max - ap->depth_min);
					t = 1.f - t;
					img_depth.SetPixel(i, j, Vec3f(t, t, t));
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
}
