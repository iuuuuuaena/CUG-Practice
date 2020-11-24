#pragma once
#include <iostream>
class ArcParse
{
public:
	ArcParse();
	ArcParse(int argc, char **argv);
	~ArcParse();

	char *input_file = NULL;
	int width = 100;
	int height = 100;
	char *output_file = NULL;
	float depth_min = 0;
	float depth_max = 1;
	char *depth_file = NULL;
};

