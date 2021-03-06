#define OUTER_CPTS  22           /* Fixed maximum number of control points for outer contour */
#define INNER_CPTS  16           /* Fixed maximum number of control points for inner contour */

// number 9
// author R. Gebauer
GLfloat cpts[OUTER_CPTS+INNER_CPTS][3]={
//outer control points
	{2,1.2,0},{2,0.2,0},{2,1.2,0},
	{2,0.2,0},{8.2,0.2,0},{18.4,7.5,0},
	{18.4,17,0},{18.4,22.5,0},{14,28,0},
	{9.6,28,0},{5.5,28,0},{1.4,23.5,0},
	{1.4,19,0},{1.4,14.8,0},{4.7,10.6,0},
	{8,10.6,0},{10.6,10.6,0},{11.6,10.6,0},
	{13.9,12.6,0},{13.9,6.9,0},{5.95,1.2,0},
	{2,1.2,0},
//inner control points
	{14.2,14.2,0},{14.4,14.6,0},{14.4,14.6,0},
	{14.6,18,0},{14.6,22.4,0},{11.8,26.8,0},
	{9,26.8,0},{6.9,26.8,0},{4.8,23.9,0},
	{4.8,21,0},{4.8,16.7,0},{7.4,12.4,0},
	{10,12.4,0},{11.45,12.4,0},{12.9,13.1,0},
	{14.2,14.2,0}
};