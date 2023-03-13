/*  Project (Graphics)

 Names:
 1- Osama Ala'a         20198009
 2- Abdallah Osama      20198053
 3-Gamal hanafi khalil  20198021
 4-Mohammed Ramadan     20198021
 5-Amr Hosney           20198059

*/
#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#include <tchar.h>
#include <windows.h>
#include <cmath>
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#define FILE_MENU_EXIT 1000
using namespace std;
bool random = false;

string data = "";

int counter = 0;

int menu=0;

int counter_click_rectangle=0;
// Round Function
int ROUND(double x)
{
    return (int)(x+0.5);
}


struct rect_point
{
    int x;
    int y;
    rect_point()
    {
        x=0;
        y=0;
    }
};

static rect_point left_bottom;
static rect_point right_top;
static rect_point right_bottom;
static rect_point left_top;

void DrawLine_window(HDC hdc, int x1,int y1,int x2,int y2,COLORREF color);
bool Clipping(HDC hdc,double x,double y,rect_point left_bottom,rect_point left_top,rect_point right_top,rect_point right_bottom,COLORREF color);
void DrawCircle_Clipping(HDC hdc, int xc,int yc, int R, COLORREF color);

//Clipping Line by line

void DrawLine_window(HDC hdc, int x1,int y1,int x2,int y2,COLORREF color);
bool Clipping(HDC hdc,double x,double y,rect_point left_bottom,rect_point left_top,rect_point right_top,rect_point right_bottom,COLORREF color);

//Clipping Line by line
union OutCode
{
    unsigned All:4;
    struct
    {
        unsigned left:1,top:1,right:1,bottom:1;
    };
};

OutCode GetOutCode(double x,double y,int xleft,int ytop,int xright,int ybottom);
void VIntersect(double xs,double ys,double xe,double ye,int x,double *xi,double *yi);
void HIntersect(double xs,double ys,double xe,double ye,int y,double *xi,double *yi);
void CohenSuth(HDC hdc,int xs,int ys,int xe,int ye,int xleft,int ytop,int xright,int ybottom,COLORREF c);

void Draw_8_point(HDC hdc,int xc,int yc,int x,int y,COLORREF c);
void Draw_4_Points(HDC hdc, int x, int y, int xc,int yc, COLORREF c);
void Draw_8_point_Filling(HDC hdc,int xc,int yc,int x,int y,int quarter,COLORREF color);


//  variables declaration
int xx,x2,yy,y2,x3,y3,R,r,r2=0;

int n=0; // n is step_counter
int c=0; // c for color

// draw line algorithms
void Drawline1(HDC hdc, int x1,int y1,int x2,int y2,COLORREF color);
void Drawline2(HDC hdc, int x1,int y1,int x2,int y2,COLORREF c);
void Drawline3(HDC hdc,int x1,int y1,int x2,int y2,COLORREF color);

//Draw Circle
void CircleDirect(HDC hdc, int xc,int yc, int R, COLORREF color);
void CircleIterativePolar(HDC hdc, int xc,int yc, int R, COLORREF color);
void circle(HDC hdc,int xc,int yc,int R,COLORREF color);
void circle2(HDC hdc, int xc, int yc, int R, COLORREF color);
void DrawCircle_Filling(HDC hdc,int xc,int yc,int R,int quarter,COLORREF color);

//Draw Ellipse
void DrawEllipse_Direct(HDC hdc,int xc,int yc,int R,int r2,COLORREF c);
void DrawEllipse_Direct(HDC hdc,int xc,int yc,int R,int r2,COLORREF c);
void DrawEllipse_Polar(HDC hdc,int xc,int yc,int r,int r2,COLORREF c);


struct Save_Point
{
    string Function_Name;
    int x1,x2;
    int y1,y2;
    int R,r2;
    int Rc,Gc,Bc;
    int quarter;
    rect_point left_bottom;
    rect_point right_top;
    rect_point right_bottom;
    rect_point left_top;
    int xleft;
    int ytop;
    int xright;
    int ybottom;

    Save_Point()
    {
        this->Function_Name="";
        this->x1=0;
        this->x2=0;
        this->y1=0;
        this->y2=0;
        this->R=0;
        this->r2=0;
        this->Rc=255;
        this->Gc=255;
        this->Bc=255;

    }

    Save_Point(string Function_Name,int x1,int y1,int R,int r2,int Rc,int Gc,int Bc,char e) //Ellipse
    {
        this->Function_Name=Function_Name;
        this->x1=x1;
        this->R=R;
        this->r2=r2;
        this->y1=y1;
        this->Rc=Rc;
        this->Gc=Gc;
        this->Bc=Bc;
    }
    Save_Point(string Function_Name,int x1,int y1,int R,int Rc,int Gc,int Bc) //Circle
    {
        this->Function_Name=Function_Name;
        this->x1=x1;
        this->R=R;
        this->y1=y1;
        this->Rc=Rc;
        this->Gc=Gc;
        this->Bc=Bc;
    }
    Save_Point(string Function_Name,int x1,int y1,int R,int quarter,int Rc,int Gc,int Bc,string f) //Filling
    {
        this->Function_Name=Function_Name;
        this->x1=x1;
        this->R=R;
        this->y1=y1;
        this->Rc=Rc;
        this->Gc=Gc;
        this->Bc=Bc;
        this->quarter=quarter;
    }
    Save_Point(string Function_Name,int x1,int y1,int x2,int y2,int Rc,int Gc,int Bc)  //Line
    {
        this->Function_Name=Function_Name;
        this->x1=x1;
        this->x2=x2;
        this->y1=y1;
        this->y2=y2;
        this->Rc=Rc;
        this->Gc=Gc;
        this->Bc=Bc;
    }
    Save_Point(string Function_Name,rect_point left_bottom,rect_point right_bottom,rect_point left_top,rect_point right_top,int Rc,int Gc,int Bc)//Rectangle
    {
        this->Function_Name=Function_Name;
        this->left_bottom=left_bottom;
        this->right_top=right_top;
        this->right_bottom=right_bottom;
        this->left_top=left_top;
        this->Rc=Rc;
        this->Gc=Gc;
        this->Bc=Bc;

    }
    Save_Point(string Function_Name,int x1,int y1,int x2,int y2,int xleft,int ytop,int xright,int ybottom,int Rc,int Gc,int Bc)//clipping line
    {
        this->Function_Name=Function_Name;
        this->x1=x1;
        this->x2=x2;
        this->y1=y1;
        this->y2=y2;
        this->xleft=xleft;
        this->xright=xright;
        this->ytop=ytop;
        this->ybottom=ybottom;
        this->Rc=Rc;
        this->Gc=Gc;
        this->Bc=Bc;
    }
};
const vector<string> Split(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;
    for(auto n:s)
    {
        if(n != c) buff+=n;
        else if(n == c && buff != "")
        {
            v.push_back(buff);
            buff = "";
        }
    }
    if(buff != "") v.push_back(buff);

    return v;
}
vector<Save_Point>Arr_Save_Point;
void Save()
{
    data = "";

    for (auto it=Arr_Save_Point.begin(); it!=Arr_Save_Point.end(); ++it)
    {
        /* Save Function of All Line */
        if(it->Function_Name=="DDLine")
        {
            data += it->Function_Name+ ","+to_string(it->x1)+","+to_string(it->y1)+","+to_string(it->x2)+","+to_string(it->y2)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";
        }
        else if(it->Function_Name=="DPLine")
        {
            data += it->Function_Name+ ","+to_string(it->x1)+","+to_string(it->y1)+","+to_string(it->x2)+","+to_string(it->y2)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";
        }
        else if(it->Function_Name=="DMLine")
        {
            data += it->Function_Name+ ","+to_string(it->x1)+","+to_string(it->y1)+","+to_string(it->x2)+","+to_string(it->y2)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";
        }


        /* save Function of ALL Circle */

        if(it->Function_Name=="DDCircle")
        {
            data += it->Function_Name+ ","+to_string(it->x1)+","+to_string(it->y1)+","+to_string(it->R)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";
        }
        else if (it->Function_Name=="DPCircle")
        {
            data += it->Function_Name+ ","+to_string(it->x1)+","+to_string(it->y1)+","+to_string(it->R)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";
        }
        else if (it->Function_Name=="DMCircle")
        {
            data += it->Function_Name+ ","+to_string(it->x1)+","+to_string(it->y1)+","+to_string(it->R)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";
        }
        else if (it->Function_Name=="MDMCircle")
        {
            data += it->Function_Name+ ","+to_string(it->x1)+","+to_string(it->y1)+","+to_string(it->R)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";
        }


        /*save Function of All Filling */

        if(it->Function_Name=="DPCircleFilling")
        {
            data += it->Function_Name+ ","+to_string(it->x1)+","+to_string(it->y1)+","+to_string(it->R)+","+to_string(it->quarter)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";
        }


        /* save Function of ALL Ellipse */
        if(it->Function_Name=="DDEllipse")
        {
            data += it->Function_Name+ ","+to_string(it->x1)+","+to_string(it->y1)+","+to_string(it->R)+","+to_string(it->r2)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";
        }
        else if(it->Function_Name=="DPEllipse")
        {
            data += it->Function_Name+ ","+to_string(it->x1)+","+to_string(it->y1)+","+to_string(it->R)+","+to_string(it->r2)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";
        }

        /* Save Rectangle Drawing */
        if(it->Function_Name=="RectDraw")
        {
            data+=it->Function_Name+","+to_string(it->left_bottom.x)+","+to_string(it->left_bottom.y)+","+to_string(it->right_bottom.x)+","+to_string(it->right_bottom.y)+","+to_string(it->left_top.x)+","+to_string(it->left_top.y)+","+to_string(it->right_top.x)+","+to_string(it->right_top.y)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";


        }
        /* Save line clipped on Rectangle Window by point*/

        if(it->Function_Name=="DrawLine_window")
        {
            data += it->Function_Name+ ","+to_string(it->x1)+","+to_string(it->y1)+","+to_string(it->x2)+","+to_string(it->y2)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";
        }
        /* Save Circle clipped on Rectangle Window by point */

        if(it->Function_Name=="DrawCircle_Clipping")
        {
            data += it->Function_Name+ ","+to_string(it->x1)+","+to_string(it->y1)+","+to_string(it->R)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";
        }

        /* save line clipped on rectangle using line*/
        if(it->Function_Name=="CohenSuth")
        {
            data += it->Function_Name+ ","+to_string(it->x1)+","+to_string(it->y1)+","+to_string(it->x2)+","+to_string(it->y2)+","+to_string(it->xleft)+","+to_string(it->ytop)+","+to_string(it->xright)+","+to_string(it->ybottom)+","+to_string(it->Rc)+","+to_string(it->Gc)+","+to_string(it->Bc)+"\n";
        }

    }
    ofstream myfile;
    myfile.open ("loadFile.txt");
    myfile << data;
    myfile.close();

}
//Load Points
void Load(HDC hdc)
{
    string Line;
    ifstream LoadFile;
    LoadFile.open("loadFile.txt");
    if (!LoadFile)
    {
        cout << "Unable to open file";
        return;
    }
    while(getline(LoadFile,Line))
    {
        vector<string> Fun_Load;
        Fun_Load=Split(Line,',');

        /* Load Function of All Line */
        if(Fun_Load[0]=="DDLine")
        {
            COLORREF c =RGB(stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]));
            Drawline1(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),c);
            Save_Point x(Fun_Load[0],stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]));
            Arr_Save_Point.push_back(x);


        }
        else if(Fun_Load[0]=="DPLine")
        {
            COLORREF c =RGB(stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]));
            Drawline3(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),c);
            Save_Point x(Fun_Load[0],stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]));
            Arr_Save_Point.push_back(x);
        }
        else if(Fun_Load[0]=="DMLine")
        {
            COLORREF c =RGB(stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]));
            Drawline2(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),c);
            Save_Point x(Fun_Load[0],stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]));
            Arr_Save_Point.push_back(x);
        }


        /* Load Function of ALL Circle */

        if(Fun_Load[0]=="DDCircle")
        {
            COLORREF c =RGB(stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]));
            CircleDirect(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),c);
            Save_Point x(Fun_Load[0],stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]));
            Arr_Save_Point.push_back(x);
        }
        else if (Fun_Load[0]=="DPCircle")
        {
            COLORREF c =RGB(stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]));
            CircleIterativePolar(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),c);
            Save_Point x(Fun_Load[0],stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]));
            Arr_Save_Point.push_back(x);
        }
        else if (Fun_Load[0]=="DMCircle")
        {
            COLORREF c =RGB(stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]));
            circle(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),c);
            Save_Point x(Fun_Load[0],stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]));
            Arr_Save_Point.push_back(x);
        }
        else if (Fun_Load[0]=="MDMCircle")
        {
            COLORREF c =RGB(stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]));
            circle2(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),c);
            Save_Point x(Fun_Load[0],stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]));
            Arr_Save_Point.push_back(x);
        }


        /*Load Function of All Filling */
        if(Fun_Load[0]=="DPCircleFilling")
        {
            COLORREF c =RGB(stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]));
            DrawCircle_Filling(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),c);

            Save_Point x(Fun_Load[0],stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]),"e");
            Arr_Save_Point.push_back(x);

        }


        /* Load Function of ALL Ellipse */

        if(Fun_Load[0]=="DDEllipse")
        {
            COLORREF c =RGB(stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]));
            DrawEllipse_Direct(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),c);
            Save_Point x(Fun_Load[0],stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]),'e');
            Arr_Save_Point.push_back(x);
        }
        else if(Fun_Load[0]=="DPEllipse")
        {
            COLORREF c =RGB(stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]));
            DrawEllipse_Polar(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),c);
            Save_Point x(Fun_Load[0],stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]),'e');
            Arr_Save_Point.push_back(x);
        }

        /* Load Function of Draw Rectangle */

        if(Fun_Load[0]=="RectDraw")
        {
            COLORREF c =RGB(stoi(Fun_Load[9]),stoi(Fun_Load[10]),stoi(Fun_Load[11]));
            Drawline1(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[5]),stoi(Fun_Load[6]),c);
            Drawline1(hdc,stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]),stoi(Fun_Load[8]),c);
            Drawline1(hdc,stoi(Fun_Load[7]),stoi(Fun_Load[8]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),c);
            Drawline1(hdc,stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[1]),stoi(Fun_Load[2]),c);
            /* Save points in array after load */
            left_bottom.x=stoi(Fun_Load[1]);
            left_bottom.y=stoi(Fun_Load[2]);
            left_top.x=stoi(Fun_Load[5]);
            left_top.y=stoi(Fun_Load[6]);
            right_bottom.x=stoi(Fun_Load[3]);
            right_bottom.y=stoi(Fun_Load[4]);
            right_top.x=stoi(Fun_Load[7]);
            right_top.y=stoi(Fun_Load[8]);

            Save_Point x("RectDraw",left_bottom,right_bottom,left_top,right_top,stoi(Fun_Load[9]),stoi(Fun_Load[10]),stoi(Fun_Load[11]));
            Arr_Save_Point.push_back(x);

        }
        if(Fun_Load[0]=="DrawLine_window")
        {

            COLORREF c =RGB(stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]));
            DrawLine_window(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),c);

            Save_Point x(Fun_Load[0],stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]));
            Arr_Save_Point.push_back(x);
        }
        if(Fun_Load[0]=="DrawCircle_Clipping")
        {
            COLORREF c =RGB(stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]));
            DrawCircle_Clipping(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),c);
            Save_Point x(Fun_Load[0],stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]));
            Arr_Save_Point.push_back(x);
        }
        if(Fun_Load[0]=="CohenSuth")
        {

            COLORREF c =RGB(stoi(Fun_Load[9]),stoi(Fun_Load[10]),stoi(Fun_Load[11]));
            CohenSuth(hdc,stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]),stoi(Fun_Load[8]),c);
            Save_Point x(Fun_Load[0],stoi(Fun_Load[1]),stoi(Fun_Load[2]),stoi(Fun_Load[3]),stoi(Fun_Load[4]),stoi(Fun_Load[5]),stoi(Fun_Load[6]),stoi(Fun_Load[7]),stoi(Fun_Load[8]),stoi(Fun_Load[9]),stoi(Fun_Load[10]),stoi(Fun_Load[11]));
            Arr_Save_Point.push_back(x);
        }
    }
}

//Clean Points//
void Clean(HDC hdc,vector<Save_Point> &Arr_Save_Point)
{

    COLORREF  c=RGB(255,255,255);

    for (auto it=Arr_Save_Point.begin(); it!=Arr_Save_Point.end(); ++it)
    {
        // Clean Function of All Line //

        if(it->Function_Name=="DDLine")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            Drawline1(hdc,it->x1,it->y1,it->x2,it->y2,c);
        }
        else if(it->Function_Name=="DPLine")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            Drawline3(hdc,it->x1,it->y1,it->x2,it->y2,c);

        }
        else if(it->Function_Name=="DMLine")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            Drawline2(hdc,it->x1,it->y1,it->x2,it->y2,c);

        }


        // Clean Function of ALL Circle //

        if(it->Function_Name=="DDCircle")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            CircleDirect(hdc,it->x1,it->y1,it->R,c);
        }
        else if (it->Function_Name=="DPCircle")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            CircleIterativePolar(hdc,it->x1,it->y1,it->R,c);
        }
        else if (it->Function_Name=="DMCircle")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            circle(hdc,it->x1,it->y1,it->R,c);
        }
        else if (it->Function_Name=="MDMCircle")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            circle2(hdc,it->x1,it->y1,it->R,c);
        }



        // Clean Function of ALL Circle Filling //
        if(it->Function_Name=="DPCircleFilling")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            DrawCircle_Filling(hdc,it->x1,it->y1,it->R,it->quarter,c);

        }



        // Clean Function of ALL Ellipse //

        if(it->Function_Name=="DDEllipse")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            DrawEllipse_Direct(hdc,it->x1,it->y1,it->R,it->r2,c);
        }
        else if(it->Function_Name=="DPEllipse")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            DrawEllipse_Polar(hdc,it->x1,it->y1,it->R,it->r2,c);
        }

        // Clean Function of Drawing Rectangle
        if(it->Function_Name=="RectDraw")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            Drawline1(hdc,it->left_bottom.x,it->left_bottom.y,it->left_top.x,it->left_top.y,c);
            Drawline1(hdc,it->left_top.x,it->left_top.y,it->right_top.x,it->right_top.y,c);
            Drawline1(hdc,it->right_top.x,it->right_top.y,it->right_bottom.x,it->right_bottom.y,c);
            Drawline1(hdc,it->right_bottom.x,it->right_bottom.y,it->left_bottom.x,it->left_bottom.y,c);
        }

        // Clean Function of Line on Rectangle of point

        if(it->Function_Name=="DrawLine_window")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            DrawLine_window(hdc,it->x1,it->y1,it->x2,it->y2,c);
        }
        // Clean Function of Circle on Rectangle of point

        if(it->Function_Name=="DrawCircle_Clipping")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            DrawCircle_Clipping(hdc,it->x1,it->y1,it->R,c);
        }

        // Clean Function of Line on Rectangle of Line
        if(it->Function_Name=="CohenSuth")
        {
            it->Rc=255;
            it->Gc=255;
            it->Bc=255;
            CohenSuth(hdc,it->x1,it->y1,it->x2,it->y2,it->xleft,it->ytop,it->xright,it->ybottom,c);
        }
    }
    Arr_Save_Point.clear();
}
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("Graphics Project_Bio_Coder");
int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{

    HWND hwnd; /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_WINLOGO);
    wincl.hIconSm = LoadIcon (NULL, IDI_WINLOGO);
   // to change the cursor shape
    wincl.hCursor = LoadCursor (NULL, IDC_HAND);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */

    /* Use White colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) RGB(255,255,0);
    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Graphics Project"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               1920,                 /* The programs width */
               1080,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}
// menu function
void menus(HWND hwnd);
HMENU hmenu;//global scope of type HMENU to handle menu to be add to window
int Rc,Gc,Bc;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    HDC hdc = GetDC(hwnd);
    static int x1,x2,x3;
    static int y1,y2,y3;
    int r,r2;
    int R;
    static int   quarter;
    if(random)
    {
        Rc = (rand()* 10000) % 255;
        Gc = (rand()* 10000) % 180;
        Bc = (rand()* 10000) % 255;
        c = RGB(Rc,Gc,Bc);
    }
    switch (message)                  /* handle the messages */
    {
    // case for creating menu
    case WM_CREATE:
        menus(hwnd);
        break;

    // for choosing command
    case WM_COMMAND:

        // for combination between screen and (in/out) put
        switch(wParam)
        {

        case 20://save
            Save();
            cout<< "Save Done !" << endl;
            break;
        case 21://load
            Load(hdc);
            cout<<"load Done !"<<endl;
            break;
        case 22://clear
            n=22;
            Clean(hdc,Arr_Save_Point);
            cout<<" clear Done !"<<endl;
            break;
        case FILE_MENU_EXIT:
            DestroyWindow(hwnd);
            break;
        case 1:
            n=1;
            cout<<"line draw by DDA"<<endl;
            break;
        case 2:
            n=2;
            cout<<"line draw by Midpoint"<<endl;
            break;
        case 3:
            n=3;
            cout<<"line draw by parametric"<<endl;
            break;
        case 4:
            n=4;
            cout<<"circle draw by direct"<<endl;
            break;
        case 5:
            n=5;
            cout<<"circle draw by polar iterative"<<endl;
            break;
        case 6:
            n=6;
            cout<<"circle draw by Midpoint"<<endl;
            break;

        case 7:
            n=7;
            cout<<"circle draw by Modified Midpoint"<<endl;
            break;

        case 8:
            n=8;
            cout<<"ellipse draw by Direct"<<endl;
            break;

        case 9:
            n=9;
            cout<<"ellipse draw by polar"<<endl;
            break;

        case 10:
            c=1;
            cout<<"color line green"<<endl;
            break;
        case 11:
            c=2;
            cout<<"color line red"<<endl;
            break;
        case 12:
            c=3;
            cout<<"color line blue"<<endl;
            break;

        case 13:
            n=13;
            cout << "filling the first quarter"<<endl;
            break;
        case 14:
            n=14;
            cout << "filling the second quarter"<<endl;
            break;
        case 15:
            n=15;
            cout << "filling the therd quarter"<<endl;
            break;
        case 16:
            n=16;
            cout << "filling the fourth quarter"<<endl;
            break;

        case 17:
            n=17;
            cout << " clipping line by point "<<endl;
            break;

        case 18:
            n=18;
            cout << "clipping circle by point"<<endl;
            break;


        case 19:
            n=19;
            cout << "clipping circle by line"<<endl;
            break;
        }

    // for first click
    case WM_LBUTTONDOWN:

        if(n== 1 || n==2 || n==3 || n== 4 || n==5 || n==6 || n==7 || n==13 || n==14 ||n==15 || n==16 || n==17 || n==18 || n==19 )//  Line, Circle (Directr,Polar,Midpoint) , clipping
        {
            xx = LOWORD(lParam);
            yy = HIWORD(lParam);

            break;
        }
        break;



    case WM_RBUTTONDOWN:

        if(n == 8 || n == 9)
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);

            break;
        }
        break;



    // case for last point
    case WM_LBUTTONUP:
        if (n==1 || n==2 || n==3)  //Line(Direct,Polar,Midpoint)
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);

            switch(n)
            {
            case 1:
                switch(c)
                {
                case 1:
                {
                    Drawline1(hdc,xx,yy,x2,y2,RGB(0,255,0));
                    Save_Point x("DDLine",xx,yy,x2,y2,0,255,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 2:
                {

                    Drawline1(hdc,xx,yy,x2,y2,RGB(255,0,0));
                    Save_Point x("DDLine",xx,yy,x2,y2,255,0,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 3:
                {

                    Drawline1(hdc,xx,yy,x2,y2,RGB(0,0,255));
                    Save_Point x("DDLine",xx,yy,x2,y2,0,0,255);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                default:
                {


                    Drawline1(hdc,xx,yy,x2,y2,RGB(0,0,0));
                    Save_Point x("DDLine",xx,yy,x2,y2,0,0,0);
                    Arr_Save_Point.push_back(x);
                }
                }
                break;
            case 2:
                switch(c)
                {
                case 1:
                {


                    Drawline2(hdc,xx,yy,x2,y2,RGB(0,255,0));
                    Save_Point x("DMLine",xx,yy,x2,y2,0,255,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 2:
                {


                    Drawline2(hdc,xx,yy,x2,y2,RGB(255,0,0));
                    Save_Point x("DMLine",xx,yy,x2,y2,255,0,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 3:
                {


                    Drawline2(hdc,xx,yy,x2,y2,RGB(0,0,255));
                    Save_Point x("DMLine",xx,yy,x2,y2,0,0,255);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                default:
                {


                    Drawline2(hdc,xx,yy,x2,y2,RGB(0,0,0));
                    Save_Point x("DMLine",xx,yy,x2,y2,0,0,0);
                    Arr_Save_Point.push_back(x);
                }
                }
                break;
            case 3:
                switch(c)
                {
                case 1:
                {
                    Drawline3(hdc,xx,yy,x2,y2,RGB(0,255,0));
                    Save_Point x("DPLine",xx,yy,x2,y2,0,255,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 2:
                {
                    Drawline3(hdc,xx,yy,x2,y2,RGB(255,0,0));
                    Save_Point x("DPLine",xx,yy,x2,y2,255,0,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 3:
                {

                    Drawline3(hdc,xx,yy,x2,y2,RGB(0,0,255));
                    Save_Point x("DPLine",xx,yy,x2,y2,0,0,255);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                default:
                {
                    Drawline3(hdc,xx,yy,x2,y2,RGB(0,0,0));
                    Save_Point x("DPLine",xx,yy,x2,y2,0,0,0);
                    Arr_Save_Point.push_back(x);
                }
                }
                break;
            }

            break;
        }
        if (n==4 || n==5 || n==6 || n==7)  //circle(Direct,Polar,Midpoint)
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            R = sqrt(((x2 - xx) * (x2 - xx)) + ((y2 - yy) * (y2 - yy))); // to calculate the redius

            switch(n)
            {
            case 4:
                switch(c)
                {
                case 1:
                {
                    CircleDirect(hdc,xx,yy,R,RGB(0,255,0));
                    Save_Point x("DDCircle",xx,yy,R,0,255,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 2:
                {


                    CircleDirect(hdc,xx,yy,R,RGB(255,0,0));
                    Save_Point x("DDCircle",xx,yy,R,255,0,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 3:
                {

                    CircleDirect(hdc,xx,yy,R,RGB(0,0,255));
                    Save_Point x("DDCircle",xx,yy,R,0,0,255);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                default:
                {
                    CircleDirect(hdc,xx,yy,R,RGB(0,0,0));
                    Save_Point x("DDCircle",xx,yy,R,0,0,0);
                    Arr_Save_Point.push_back(x);
                }
                }
                break;
            case 5:
                switch(c)
                {
                case 1:
                {

                    CircleIterativePolar(hdc,xx,yy,R,RGB(0,255,0));
                    Save_Point x("DPCircle",xx,yy,R,0,255,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 2:
                {
                    CircleIterativePolar(hdc,xx,yy,R,RGB(255,0,0));
                    Save_Point x("DPCircle",xx,yy,R,255,0,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 3:
                {


                    CircleIterativePolar(hdc,xx,yy,R,RGB(0,0,255));
                    Save_Point x("DPCircle",xx,yy,R,0,0,255);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                default:
                {
                    CircleIterativePolar(hdc,xx,yy,R,RGB(0,0,0));
                    Save_Point x("DPCircle",xx,yy,R,0,0,0);
                    Arr_Save_Point.push_back(x);
                }
                }
                break;

            case 6:
                switch(c)
                {
                case 1:
                {


                    circle(hdc,xx,yy,R,RGB(0,255,0));
                    Save_Point x("DMCircle",xx,yy,R,0,255,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 2:
                {


                    circle(hdc,xx,yy,R,RGB(255,0,0));
                    Save_Point x("DMCircle",xx,yy,R,255,0,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 3:
                {


                    circle(hdc,xx,yy,R,RGB(0,0,255));
                    Save_Point x("DMCircle",xx,yy,R,0,0,255);
                    Arr_Save_Point.push_back(x);
                    break;
                }
                default:
                {

                    circle(hdc,xx,yy,R,RGB(0,0,0));
                    Save_Point x("DMCircle",xx,yy,R,0,0,0);
                    Arr_Save_Point.push_back(x);
                }
                }
                break;


            case 7:
                switch(c)
                {
                case 1:
                {
                    circle2(hdc,xx,yy,R,RGB(0,255,0));
                    Save_Point x("MDMCircle",xx,yy,R,0,255,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }

                case 2:
                {
                    circle2(hdc,xx,yy,R,RGB(255,0,0));
                    Save_Point x("MDMCircle",xx,yy,R,255,0,0);
                    Arr_Save_Point.push_back(x);
                    break;
                }

                case 3:
                {
                    circle2(hdc,xx,yy,R,RGB(0,0,255));
                    Save_Point x("MDMCircle",xx,yy,R,0,0,255);
                    Arr_Save_Point.push_back(x);
                    break;

                }

                default:
                {
                    circle2(hdc,xx,yy,R,RGB(0,0,0));
                    Save_Point x("MDMCircle",xx,yy,R,0,0,0);
                    Arr_Save_Point.push_back(x);
                }

                }
                break;


            }
            break;
        }

        if (n==8 || n==9) // ellipse (Direct, polar)
        {
            x3 = LOWORD(lParam);
            y3 = HIWORD(lParam);
            r = ROUND(sqrt(pow(x2-xx,2.0)+pow(y2-yy,2.0)));
            r2 = ROUND(sqrt(pow(x3-xx,2.0)+pow(y3-yy,2.0)));

            switch(n)
            {
            case 8:
                switch(c)
                {
                case 1:
                {
                    DrawEllipse_Direct(hdc,xx,yy,r,r2,RGB(0,255,0));
                    Save_Point x("DPEllipse",xx,yy,r,r2,0,255,0,'e');
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 2:
                {
                    DrawEllipse_Direct(hdc,xx,yy,r,r2,RGB(255,0,0));
                    Save_Point x("DPEllipse",xx,yy,r,r2,255,0,0,'e');
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 3:
                {
                    DrawEllipse_Direct(hdc,xx,yy,r,r2,RGB(0,0,255));
                    Save_Point x("DPEllipse",xx,yy,r,r2,0,0,255,'e');
                    Arr_Save_Point.push_back(x);
                    break;
                }
                default:
                {
                    DrawEllipse_Direct(hdc,xx,yy,r,r2,RGB(0,0,0));
                    Save_Point x("DPEllipse",xx,yy,r,r2,0,0,0,'e');
                    Arr_Save_Point.push_back(x);
                }
                }
                break;

            case 9:
                switch(c)
                {
                case 1:
                    DrawEllipse_Polar(hdc,xx,yy,r,r2,RGB(0,255,0));
                    break;
                case 2:
                    DrawEllipse_Polar(hdc,xx,yy,r,r2,RGB(255,0,0));
                    break;
                case 3:
                    DrawEllipse_Polar(hdc,xx,yy,r,r2,RGB(0,0,255));
                    break;
                default:
                    DrawEllipse_Polar(hdc,xx,yy,r,r2,RGB(0,0,0));

                }
              break;
            }

            break;
        }


        if (n==13||n==14||n==15||n==16) //Circle filling first quarter
        {

            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            R = sqrt(((x2 - xx) * (x2 - xx)) + ((y2 - yy) * (y2 - yy))); // to calculate the redius

            switch(n)
            {
            case 13:
                switch(c)
                {
                case 1:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,1,RGB(0,255,0));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,0,255,0,"e");
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 2:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,1,RGB(255,0,0));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,255,0,0,"e");
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 3:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,1,RGB(0,0,255));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,0,0,255,"e");
                    Arr_Save_Point.push_back(x);
                    break;
                }
                default:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,1,RGB(0,0,0));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,0,0,0,"e");
                    Arr_Save_Point.push_back(x);
                }
                }
                break;
            case 14:
                switch(c)
                {
                case 1:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,2,RGB(0,255,0));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,0,255,0,"e");
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 2:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,2,RGB(255,0,0));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,255,0,0,"e");
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 3:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,2,RGB(0,0,255));
                    Save_Point x("DPCircleFilling",x1,y1,R,quarter,0,0,255,"e");
                    Arr_Save_Point.push_back(x);
                }
                break;
                default:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,2,RGB(0,0,0));
                    Save_Point x("DPCircleFilling",x1,y1,R,quarter,0,0,0,"e");
                    Arr_Save_Point.push_back(x);
                }
                }
                break;

            case 15:
                switch(c)
                {
                case 1:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,3,RGB(0,255,0));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,0,255,0,"e");
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 2:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,3,RGB(255,0,0));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,255,0,0,"e");
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 3:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,3,RGB(0,0,255));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,0,0,255,"e");
                    Arr_Save_Point.push_back(x);
                    break;
                }
                default:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,3,RGB(0,0,0));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,0,0,0,"e");
                    Arr_Save_Point.push_back(x);
                }

                }
                break;

            case 16:
                switch(c)
                {
                case 1:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,4,RGB(0,255,0));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,0,255,0,"e");
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 2:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,4,RGB(255,0,0));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,255,0,0,"e");
                    Arr_Save_Point.push_back(x);
                    break;
                }
                case 3:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,4,RGB(0,0,255));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,0,0,255,"e");
                    Arr_Save_Point.push_back(x);
                    break;
                }
                default:
                {
                    DrawCircle_Filling(hdc,xx,yy,R,4,RGB(0,0,0));
                    Save_Point x("DPCircleFilling",xx,yy,R,quarter,0,0,0,"e");
                    Arr_Save_Point.push_back(x);
                }
                }
                break;
            }
        }
        // clipping
        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
void menus(HWND hWnd)
{
    hmenu=CreateMenu();

    HMENU hfileMenu=CreateMenu();
    HMENU shape_menu=CreateMenu();
    HMENU color_menu=CreateMenu();
    HMENU Line_menu=CreateMenu();
    HMENU fill_menu=CreateMenu();
    HMENU Circle_menu=CreateMenu();
    HMENU Ellipse_menu=CreateMenu();
    HMENU Clipping_menu=CreateMenu();
    HMENU Quarter_menu=CreateMenu();
    // for header menu
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hfileMenu,"Menu");

    // for inested menu (shapes)
    AppendMenu(hfileMenu,MF_POPUP,(UINT_PTR)shape_menu,"shapes");

    // for inested menu (lines)
    AppendMenu(shape_menu,MF_POPUP,(UINT_PTR)Line_menu,"Line's Algorithms");

    AppendMenu(Line_menu,MF_STRING,(UINT_PTR)1,"DDA");     // num
    AppendMenu(Line_menu,MF_STRING,(UINT_PTR)2,"Midpoint");
    AppendMenu(Line_menu,MF_STRING,(UINT_PTR)3,"parametric");

    AppendMenu(shape_menu,MF_POPUP,(UINT_PTR)Circle_menu,"Circle's Algorithms");

    AppendMenu(Circle_menu,MF_STRING,(UINT_PTR)4,"Direct");
    AppendMenu(Circle_menu,MF_STRING,(UINT_PTR)5,"Polar iterative Polar");
    AppendMenu(Circle_menu,MF_STRING,(UINT_PTR)6,"Midpoint");
    AppendMenu(Circle_menu,MF_STRING,(UINT_PTR)7,"Modified Midpoint");


    AppendMenu(shape_menu,MF_POPUP,(UINT_PTR)Ellipse_menu,"Ellipse's Algorithms");

    AppendMenu(Ellipse_menu,MF_STRING,(UINT_PTR)8,"Direct");
    AppendMenu(Ellipse_menu,MF_STRING,(UINT_PTR)9,"Polar");

    AppendMenu(hfileMenu,MF_POPUP,(UINT_PTR)color_menu,"Color");

    AppendMenu(color_menu,MF_STRING,(UINT_PTR)10,"Green");
    AppendMenu(color_menu,MF_STRING,(UINT_PTR)11,"Red");
    AppendMenu(color_menu,MF_STRING,(UINT_PTR)12,"Blue");


    AppendMenu(hfileMenu,MF_POPUP,(UINT_PTR)Quarter_menu,"Quarter circle fill");

    AppendMenu(Quarter_menu,MF_STRING,(UINT_PTR)13,"1st quarter");
    AppendMenu(Quarter_menu,MF_STRING,(UINT_PTR)14,"2nd quarter");
    AppendMenu(Quarter_menu,MF_STRING,(UINT_PTR)15,"3rd quarter");
    AppendMenu(Quarter_menu,MF_STRING,(UINT_PTR)16,"4th quarter");

    AppendMenu(hfileMenu,MF_POPUP,(UINT_PTR)Clipping_menu,"Clipping");

    AppendMenu(Clipping_menu,MF_STRING,(UINT_PTR)17,"Line Clipping by point");
    AppendMenu(Clipping_menu,MF_STRING,(UINT_PTR)18,"Circle Clipping by point");
    AppendMenu(Clipping_menu,MF_STRING,(UINT_PTR)19,"Circle Clipping by Line");

    AppendMenu(hfileMenu,MF_STRING,20,"Save");
    AppendMenu(hfileMenu,MF_STRING,21,"Load");
    AppendMenu(hfileMenu,MF_STRING,22,"Clean");

    AppendMenu(hfileMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hfileMenu,MF_STRING,FILE_MENU_EXIT,"EXIT");

    SetMenu(hWnd,hmenu);
};

void Drawline1(HDC hdc,int x1,int y1o,int x2,int y2,COLORREF c)//DDA algorithm
{
    int dx=x2-x1;
    int dy=y2-y1o;
    if(abs(dx)>=abs(dy))
    {
        double slope=(double)dy/dx;
        if(x1>x2)
        {
            swap(x1,x2);
            swap(y1o,y2);
        }
        for(int x=x1; x<=x2; x++)
        {
            int y=ROUND(y1o+(x-x1)*slope);
            SetPixel(hdc,x,y,c);
        }
    }
    else
    {
        double slope=(double)dx/dy;
        if(y1o>y2)
        {
            swap(x1,x2);
            swap(y1o,y2);
        }
        for(int y=y1o; y<=y2; y++)
        {
            int x=ROUND(x1+(y-y1o)*slope);
            SetPixel(hdc,x,y,c);
        }
    }
}

void Drawline2(HDC hdc, int x1,int y1o,int x2,int y2,COLORREF c)//line midpoint algorithm
{
    int  dx=x2-x1;
    int dy=y2-y1o;
    if(abs(dx) >= abs(dy))
    {
        if(dx < 0)
        {
            swap(x1,x2);
            swap(y1o,y2);
            dx = -dx;
            dy = -dy;
        }
        int x=x1, y=y1o;
        SetPixel(hdc, x, y, c);
        if(dy>=0)
        {
            int d = dx - 2 * dy;
            int d1 = 2*dx - 2*dy;
            int d2 = -2*dy;
            while(x<x2)
            {
                if(d<=0)
                {
                    d+=d1;
                    x++;
                    y++;
                }
                else
                {
                    d+=d2;
                    x++;
                }
                SetPixel(hdc, x, y, c);

            }
        }
        else
        {
            int d = dx + 2 * dy;
            int d1 = 2*dx + 2*dy;
            int d2 = 2*dy;

            while(x<x2)
            {
                if(d<=0)
                {
                    d+=d1;
                    x++;
                    y--;
                }
                else
                {
                    d+=d2;
                    x++;
                }
                SetPixel(hdc, x, y, c);

            }
        }
    }
    else
    {
        if(dy<0)
        {
            swap(x1,x2);
            swap(y1o,y2);

            dx = -dx;
            dy = -dy;
        }

        int x=x1, y=y1o;
        SetPixel(hdc, x, y, c);
        if(dx>=0)
        {
            double d = -2*dx + dy;
            int d1 = -2*dx + 2*dy;
            int d2 = -2*dx;

            while(y<y2)
            {
                if(d<=0)
                {
                    d+=d1;
                    x++;
                    y++;
                }
                else
                {
                    d+=d2;
                    y++;
                }
                SetPixel(hdc, x, y, c);

            }
        }
        else
        {
            double d = 2*dx + dy;
            int d1 = 2*dx + 2*dy;
            int d2 = 2*dx;

            while(y<y2)
            {
                if(d<=0)
                {
                    d+=d1;
                    x--;
                    y++;
                }
                else
                {
                    d+=d2;
                    y++;
                }
                SetPixel(hdc, x, y, c);
            }
        }
    }
}

void Drawline3(HDC hdc,int x1,int y1o,int x2,int y2,COLORREF c)//parametric line algorithm
{
    double dt=(double)1.0/max(abs(x2-x1),abs(y2-y1o));
    for(double t = 0; t<=1; t+=dt)
    {
        double x=x1+t*(x2-x1);
        double y=y1o+t*(y2-y1o);
        SetPixel(hdc,ROUND(x),ROUND(y),c);
    }
}

// draw circle algorithms

void Draw8Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color)
{
    SetPixel(hdc, xc + a, yc + b, color);
    SetPixel(hdc, xc - a, yc + b, color);
    SetPixel(hdc, xc - a, yc - b, color);
    SetPixel(hdc, xc + a, yc - b, color);
    SetPixel(hdc, xc + b, yc + a, color);
    SetPixel(hdc, xc - b, yc + a, color);
    SetPixel(hdc, xc - b, yc - a, color);
    SetPixel(hdc, xc + b, yc - a, color);
}

void CircleDirect(HDC hdc, int xc, int yc, int R, COLORREF color) // based on circle equation
{
    int x = 0, y = R;
    int R2 = R * R;
    Draw8Points(hdc, xc, yc, x, y, color);
    while (x < y)
    {
        x++;
        y = round(sqrt((double)(R2 - x * x)));
        Draw8Points(hdc, xc, yc, x, y, color);
    }
}

void CircleIterativePolar(HDC hdc, int xc, int yc, int R, COLORREF color) // based on theta value
{
    double x = R, y = 0;
    double dtheta = 1.0 / R;
    double cdtheta = cos(dtheta), sdtheta = sin(dtheta);
    Draw8Points(hdc, xc, yc, R, 0, color);
    while (x > y)
    {
        double x1 = x * cdtheta - y * sdtheta;
        y = x * sdtheta + y * cdtheta;
        x = x1;
        Draw8Points(hdc, xc, yc, round(x), round(y), color);
    }
}

void circle(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=0,y=R;
    int d=1-R;
    Draw8Points(hdc,xc,yc,x,y,color);
    while(x<y)
    {
        if(d<0)
            d+=2*x+2;
        else
        {
            d+=2*(x-y)+5;
            y--;
        }
        x++;
        Draw8Points(hdc,xc,yc,x,y,color);
    }
}


void circle2(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    int x = 0, y = R;
    int d = 1 - R;
    int d1 = 3, d2 = 5 - 2 * R;
    Draw8Points(hdc, xc, yc, x, y, color);
    while (x < y)
    {
        if (d < 0)
        {
            d += d1;
            d2 += 2;
        }
        else
        {
            d += d2;
            d2 += 4;
            y--;
        }
        d1 += 2;
        x++;
        Draw8Points(hdc, xc, yc, x, y, color);
    }
}

// drawing ellipse

void Draw_4_Points(HDC hdc, int x, int y, int xc,int yc, COLORREF color)
{

    SetPixel(hdc, xc+x, yc+y, color);
    SetPixel(hdc, xc-x, yc+y, color);
    SetPixel(hdc, xc-x, yc-y, color);
    SetPixel(hdc, xc+x, yc-y, color);

}


void DrawEllipse_Direct(HDC hdc,int xc,int yc,int R,int r2,COLORREF c)
{

    double x=R;
    int y=0;

    Draw_4_Points( hdc,  R,  0,  xc, yc,  c);
    while(x>=0)
    {
        x-=0.01;
        y= abs(r2*sqrt(1-(pow(x,2)/pow(R,2))));
        Draw_4_Points( hdc,  x,  y,  xc, yc,  c);
    }
}



void DrawEllipse_Polar(HDC hdc,int xc,int yc,int r,int r2,COLORREF c)
{
    double dtheta=1.0/r;
    for(double theta=0.0; theta<6.28; theta+=dtheta)
    {
        double x=xc+r2*cos(theta);
        double y=yc+r*sin(theta);
        SetPixel(hdc,ROUND(x),ROUND(y),c);
    }
}

// circle filling
void Draw_8_point_Filling(HDC hdc,int xc,int yc,int x,int y,int quarter,COLORREF color)
{
    if(quarter==2)
    {
        SetPixel(hdc,xc+x,yc+y,color);
        SetPixel(hdc,xc-x,yc+y,color);
        SetPixel(hdc,xc+x,yc-y,color);
        SetPixel(hdc,xc-x,yc-y,color);
        SetPixel(hdc,xc+y,yc+x,color);
        SetPixel(hdc,xc-y,yc+x,color);
        SetPixel(hdc,xc+y,yc-x,color);
        SetPixel(hdc,xc-y,yc-x,color);
        Drawline1(hdc,xc,yc,xc-x,yc-y,color);
        Drawline1(hdc,xc,yc,xc-y,yc-x,color);

    }
    if(quarter==4)
    {
        SetPixel(hdc,xc+x,yc+y,color);
        SetPixel(hdc,xc-x,yc+y,color);
        SetPixel(hdc,xc+x,yc-y,color);
        SetPixel(hdc,xc-x,yc-y,color);
        SetPixel(hdc,xc+y,yc+x,color);
        SetPixel(hdc,xc-y,yc+x,color);
        SetPixel(hdc,xc+y,yc-x,color);
        SetPixel(hdc,xc-y,yc-x,color);
        Drawline1(hdc,xc,yc,xc+x,yc+y,color);
        Drawline1(hdc,xc,yc,xc+y,yc+x,color);

    }
    if(quarter==3)
    {
        SetPixel(hdc,xc+x,yc+y,color);
        SetPixel(hdc,xc-x,yc+y,color);
        SetPixel(hdc,xc+x,yc-y,color);
        SetPixel(hdc,xc-x,yc-y,color);
        SetPixel(hdc,xc+y,yc+x,color);
        SetPixel(hdc,xc-y,yc+x,color);
        SetPixel(hdc,xc+y,yc-x,color);
        SetPixel(hdc,xc-y,yc-x,color);
        Drawline1(hdc,xc,yc,xc-x,yc+y,color);
        Drawline1(hdc,xc,yc,xc-y,yc+x,color);

    }
    if(quarter==1)
    {
        SetPixel(hdc,xc+x,yc+y,color);
        SetPixel(hdc,xc-x,yc+y,color);
        SetPixel(hdc,xc+x,yc-y,color);
        SetPixel(hdc,xc-x,yc-y,color);
        SetPixel(hdc,xc+y,yc+x,color);
        SetPixel(hdc,xc-y,yc+x,color);
        SetPixel(hdc,xc+y,yc-x,color);
        SetPixel(hdc,xc-y,yc-x,color);
        Drawline1(hdc,xc,yc,xc+x,yc-y,color);
        Drawline1(hdc,xc,yc,xc+y,yc-x,color);
    }
}

void DrawCircle_Filling(HDC hdc,int xc,int yc,int R,int quarter,COLORREF color)
{
    double dtheta=1.0/R;
    double c=std::cos(dtheta);
    double s=std::sin(dtheta);
    double x=R;
    double y=0;
    Draw_8_point_Filling(hdc,xc,yc,R,0,quarter,color);
    while (x>y)
    {
        double x1=x*c-y*s;
        y=x*s+y*c;
        x=x1;
        Draw_8_point_Filling(hdc,xc,yc,ROUND(x),ROUND(y),quarter,color);
    }
}
/*  Make the class name into a global variable  */
bool Clipping(HDC hdc,double x,double y,rect_point left_bottom,rect_point left_top,rect_point right_top,rect_point right_bottom,COLORREF color)
{
    if((x>left_bottom.x && x>left_top.x) && (y<left_bottom.y && y>left_top.y) && (x>left_top.x && x<right_top.x) &&(y>left_top.y && y>right_top.y) && (x<right_top.x && x<right_bottom.x) &&(y>right_top.y && y<right_bottom.y)&&(x>left_bottom.x && x<right_bottom.x) && (y<left_bottom.y && y<right_bottom.y))
        return false;
    return true;
}

void DrawLine_window(HDC hdc, int x1,int y1,int x2,int y2,COLORREF color)
{
    double dt=(double)1.0/std::max(abs(x2-x1),abs(y2-y1));
    for(double t = 0; t<=1; t+=dt)
    {
        double x=x1+t*(x2-x1);
        double y=y1+t*(y2-y1);
        if(!Clipping(hdc,x,y,left_bottom,left_top,right_top,right_bottom,color))
        {
            SetPixel(hdc,ROUND(x),ROUND(y),color);
        }
    }


}

void DrawCircle_Clipping(HDC hdc, int xc,int yc, int R, COLORREF color)
{
    double dtheta=1.0/R;
    for( double theta=0; theta< 6.28; theta+=dtheta)
    {
        int x=ROUND(xc+R*std::cos(theta));
        int y=ROUND(yc+R*std::sin(theta));
        if(!Clipping(hdc,x,y,left_bottom,left_top,right_top,right_bottom,color))
        {
            SetPixel(hdc,x,y,color);

        }

    }
}

OutCode GetOutCode(double x,double y,int xleft,int ytop,int xright,int ybottom)
{
    OutCode out;
    out.All=0;
    if(x<xleft)out.left=1;
    else if(x>xright)out.right=1;
    if(y<ytop)out.top=1;
    else if(y>ybottom)out.bottom=1;
    return out;
}

void VIntersect(double xs,double ys,double xe,double ye,int x,double *xi,double *yi)
{

    *xi=x;
    *yi=ys+(x-xs)*(ye-ys)/(xe-xs);
}


void HIntersect(double xs,double ys,double xe,double ye,int y,double *xi,double *yi)
{
    *yi=y;
    *xi=xs+(y-ys)*(xe-xs)/(ye-ys);
}


void CohenSuth(HDC hdc,int xs,int ys,int xe,int ye,int xleft,int ytop,int xright,int ybottom,COLORREF c)
{
    double x1=xs,y1=ys,x2=xe,y2=ye;
    OutCode out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
    OutCode out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);

    while( (out1.All || out2.All) && !(out1.All & out2.All))
    {
        double xi,yi;
        if(out1.All)
        {
            if(out1.left)VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out1.top)HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out1.right)VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x1=xi;
            y1=yi;
            out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
        }
        else
        {
            if(out2.left)VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out2.top)HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out2.right)VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x2=xi;
            y2=yi;
            out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
        }
    }

    if(!out1.All && !out2.All)
    {
        Drawline1(hdc,x1,y1,x2,y2,c);
    }
}
