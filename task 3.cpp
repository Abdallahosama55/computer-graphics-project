
/*  Task 3 (Graphics)

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
#include <math.h>
#include <cmath>
#include <windows.h>
#include <iostream>
using namespace std;
void Draw8Points(HDC hdc,int xc,int yc, int a, int b,COLORREF color)
{
    SetPixel(hdc, xc+a, yc+b, color);
    SetPixel(hdc, xc-a, yc+b, color);
    SetPixel(hdc, xc-a, yc-b, color);
    SetPixel(hdc, xc+a, yc-b, color);
    SetPixel(hdc, xc+b, yc+a, color);
    SetPixel(hdc, xc-b, yc+a, color);
    SetPixel(hdc, xc-b, yc-a, color);
    SetPixel(hdc, xc+b, yc-a, color);
}

void circle(HDC hdc,int xc,int yc, int R,COLORREF c)
{
    int x=0,y=R;
    int d=1-R;
    int d1=3, d2=5-2*R;
    Draw8Points(hdc,xc,yc,x,y,c);
    while(x<y)
    {
        if(d<0)
        {
            d+=d1;
            d2+=2;
        }
        else
        {
            d+=d2;
            d2+=4;
            y--;
        }
        d1+=2;
        x++;
        Draw8Points(hdc,xc,yc,x,y,c);
    }
}
int ROUND(double x)
{
    return (int)(x+0.5);
}
void DrawLine(HDC hdc,int x1,int y1,int x2,int y2,COLORREF c)
{
    double dt=(double)1.0/max(abs(x2-x1),abs(y2-y1));
    for(double t = 0; t<=1; t+=dt)
    {
        double x=x1+t*(x2-x1);
        double y=y1+t*(y2-y1);
        SetPixel(hdc,ROUND(x),ROUND(y),c);
    }
}
void HermitCurve(HDC hdc,int x0,int y0,int s0_x,int s0_y,int x1,int y1,int s1_x,int s1_y)
{
    double alf1=2*x0+s0_x-2*x1+s1_x;
    double beta1=-3*x0-2*s0_x+3*x1-s1_x;
    double gamma1=s0_x;
    double sigma1=x0;

    double alf2=2*y0+s0_y-2*y1+s1_y;
    double beta2=-3*y0-2*s0_y+3*y1-s1_y;
    double gamma2=s0_y;
    double sigma2=y0;
    for(double t=0; t<=1; t+=0.001)
    {
        double t3=pow(t,3);
        double t2=pow(t,2);
        double x=(alf1*t3)+(beta1*t2)+(gamma1*t)+sigma1;
        double y=(alf2*t3)+(beta2*t2)+(gamma2*t)+sigma2;
        SetPixel(hdc,x,y,RGB(0,0,255));
    }
}
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
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


/*  This function is called by the Windows function DispatchMessage()  */
int click=1;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
    case WM_LBUTTONDBLCLK:
        if(click==1)
        {
            circle(hdc,300,300,100,RGB(0,0,0));
            click++;
            break;
        }
        if(click==2)
        {
            circle(hdc,370,270,15,RGB(0,0,255));
            click++;
            break;
        }
        if(click==3)
        {
            circle(hdc,230,270,15,RGB(0,0,255));
            click++;
            break;
        }
        if(click==4)
        {
            click++;
            break;
        }
        if(click==5)
        {
            HermitCurve(hdc,270,370,100,100,330,370,0,0);
            click++;
            break;
        }
        if(click==6)
        {
            DrawLine(hdc,330,240,370,170,RGB(0,0,255));
            click++;
            break;
        }
        if(click==7)
        {
            DrawLine(hdc,310,230,280,170,RGB(0,0,255));
            click++;
            break;
        }
        if(click==8)
        {
            DrawLine(hdc,290,225,250,170,RGB(0,0,255));
            click++;
            break;
        }
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
