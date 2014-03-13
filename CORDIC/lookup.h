#define	TABLE_LENGTH		10

struct rotation_info {
	int index;
	double tangent;
	double angle;
};

struct rotation_info rotation_table[TABLE_LENGTH] = {
	{0, 	1, 		45},
	{1, 	0.5, 		26.56505118},
	{2, 	0.25,		14.03624347},
	{3,	0.125,		7.125016349},
	{4,	0.0625,		3.576334375},
	{5,	0.03125,	1.789910608},
	{6,	0.015625,	0.89517371},
	{7,	0.0078125,	0.447614171},
	{8,	0.00390625,	0.2238105},
	{9,	0.001953125,	0.111905677}
};
