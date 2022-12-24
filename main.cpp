#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

VOID OnPaint(HDC hdc)
{
    Graphics graphics(hdc);
    Pen      pen(Color(255, 0, 0, 255));
    //string
    SolidBrush  brush(Color(255, 0, 0, 255));
    FontFamily  fontFamily(L"Times New Roman");
    Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
    PointF      pointF(10.0f, 20.0f);

   //arrow
    Pen pen2(Color(255, 0, 0, 255), 8);
    pen2.SetStartCap(LineCapArrowAnchor);
    pen2.SetEndCap(LineCapRoundAnchor);
    //paths
    GraphicsPath path;
    Pen penJoin(Color(255, 0, 0, 255), 8);

    path.StartFigure();
    path.AddLine(Point(50, 200), Point(100, 200));
    path.AddLine(Point(100, 200), Point(100, 250));

    penJoin.SetLineJoin(LineJoinBevel);
    //dashed lines
    REAL dashValues[4] = {5, 2, 15, 4};
    Pen blackPen(Color(255, 0, 0, 0), 5);
    blackPen.SetDashPattern(dashValues, 4);

    //fill a shape
    SolidBrush solidBrush(Color(255, 255, 0, 0));

    //curves
    Point points[] = {
        Point(0,100),
        Point(50, 80),
        Point(100, 20),
        Point(150, 80),
        Point(200, 100)
    };
    Pen pen3(Color(255, 0, 0, 255));

    Point points2[] = {Point(20, 50),
                  Point(100, 10),
                  Point(200, 100),
                  Point(300, 50),
                  Point(400, 80)};

    Point p1(10, 100);   // start point
    Point c1(100, 10);   // first control point
    Point c2(150, 150);  // second control point
    Point p2(200, 100);  // end point


    /*draw the things*/

    //## draw bezier curve
    graphics.DrawBezier(&pen3, p1, c1, c2, p2);


    //## simple curve
    //graphics.DrawCurve(&pen3, points, 5);

    //## curve with tensions
    //graphics.DrawCurve(&pen3, points2, 5, 0.0f);  // tension 0.0
    //graphics.DrawCurve(&pen3, points2, 5, 0.6f);  // tension 0.6
    //graphics.DrawCurve(&pen3, points2, 5, 1.0f);  // tension 1.0

    //## brush solid object
    //graphics.FillEllipse(&solidBrush, 0, 0, 100, 60);

    graphics.DrawLine(&blackPen, Point(5, 5), Point(405, 5));

    graphics.DrawPath(&penJoin, &path);

    graphics.DrawLine(&pen2, 20, 175, 300, 175);

    //## draw string
    //graphics.DrawString(L"Hello World!", -1, &font, pointF, &brush);

    //## draw simple line
    //graphics.DrawLine(&pen, 0, 0, 200, 100);

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
   HWND                hWnd;
   MSG                 msg;
   WNDCLASS            wndClass;
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR           gdiplusToken;

   // Initialize GDI+.
   GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

   wndClass.style          = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc    = WndProc;
   wndClass.cbClsExtra     = 0;
   wndClass.cbWndExtra     = 0;
   wndClass.hInstance      = hInstance;
   wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
   wndClass.lpszMenuName   = NULL;
   wndClass.lpszClassName  = TEXT("GettingStarted");

   RegisterClass(&wndClass);

   hWnd = CreateWindow(
      TEXT("GettingStarted"),   // window class name
      TEXT("Getting Started"),  // window caption
      WS_OVERLAPPEDWINDOW,      // window style
      CW_USEDEFAULT,            // initial x position
      CW_USEDEFAULT,            // initial y position
      CW_USEDEFAULT,            // initial x size
      CW_USEDEFAULT,            // initial y size
      NULL,                     // parent window handle
      NULL,                     // window menu handle
      hInstance,                // program instance handle
      NULL);                    // creation parameters

   ShowWindow(hWnd, iCmdShow);
   UpdateWindow(hWnd);

   while(GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }

   GdiplusShutdown(gdiplusToken);
   return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
   WPARAM wParam, LPARAM lParam)
{
   HDC          hdc;
   PAINTSTRUCT  ps;

   switch(message)
   {
   case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      OnPaint(hdc);
      EndPaint(hWnd, &ps);
      return 0;
   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
} // WndProc
