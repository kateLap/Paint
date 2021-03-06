#include "MYpaint.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangles.h"
#include "Point.h"
#include "Painting.h"
#include <list>
#include "MyException.h"
#include "Stack.cpp"
#include "commdlg.h"

#define MAX_LOADSTRING 100
#define SCR_LENGHT 1100
#define SCR_HEIGHT 500

// Глобальные переменные:
HINSTANCE hInst;                            // текущий экземпляр
WCHAR szWindowClass[MAX_LOADSTRING];        // имя класса главного окна

HBITMAP hBitmap;
BITMAP bm;
HDC screen_buf, screen_buf_first;
HBITMAP screen_bm, screen_bm_first;
int height;
int width;

Shape* draw_object;
Painting* painting;

list<Shape*> shape_list;
list<Painting*> painting_list;
Stack<COLORREF>  palette_stack;

int element = 0;

COLORREF pencil = BLACK_COLOR, brush = WHITE_COLOR;
int pencil_size = 4;

bool flag = 1;

enum Shapes { LINE, RECTANGLE, CIRCLE, POINTs };
Shapes mode = LINE;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ColorChoise(HWND, UINT, WPARAM, LPARAM);
//void OpenMetaFile(HWND hWnd, HDC memDC, WPARAM wParam, LPARAM lParam);

//Прототипы функций
void SaveFile(HWND hWnd, HDC windowDC);
void ButtonDown(HDC hdc, LPARAM lParam);
void LastState(HDC hdc);
void Stack_filling();



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDC_MYPAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYPAINT));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//Регистрация класса окна
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PENCIL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MYPAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_FLOWER));

    return RegisterClassExW(&wcex);
}


//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: Сохраняет обработку экземпляра и создает главное окно.

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, (LPCWSTR)"My Paint" , WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	//HBITMAP hBitmap;
	//BITMAP bm;
	HDC  hmdc; //объявляем ещё один контекст изображения hmdc

	switch (message)
	{
	case WM_CREATE:
	{
		Stack_filling();//заполнение стека цветами

		try
		{
			//загрузка изображения

			hBitmap = (HBITMAP)LoadImage(hInst, "C:\\ProgramProjects\\1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


			if ((!hBitmap))
			{
				String error("Ошибка открытия файла");
				throw InputException(1, error);
			}
		}
		catch (InputException & exception)
		{
			exception.Input(hWnd);
		}


		if (::GetObject(hBitmap, sizeof(BITMAP), (PSTR)&bm) != sizeof(BITMAP))//получить информацию об изображении
		{
			height = SCR_HEIGHT;
			width = SCR_LENGHT;
		}
		else
		{
			height = bm.bmHeight;
			width = bm.bmWidth;
		}


		hdc = GetDC(hWnd);

		screen_buf = CreateCompatibleDC(hdc); //создание совместимого с оконным контекста памяти
		screen_buf_first = CreateCompatibleDC(hdc);  //контекст памяти для хранения фонового изображения

		screen_bm = CreateCompatibleBitmap(hdc, width, height);
		screen_bm_first = CreateCompatibleBitmap(hdc, width, height);

		SelectObject(screen_buf, screen_bm);
		SelectObject(screen_buf_first, screen_bm_first);
		Rectangle(screen_buf_first, 0, 0, width, height);

		if (hBitmap)
		{
			hmdc = CreateCompatibleDC(hdc); //создание совместимого с оконным контекста памяти

			SelectObject(hmdc, hBitmap); //Выбор объекта картинку

			BitBlt(screen_buf_first, 0, 0, width, height, hmdc, 0, 0, SRCCOPY);//помещение картинки на экран в точку 0, 0

			DeleteDC(hmdc);
		}

		BitBlt(screen_buf, 0, 0, width, height, screen_buf_first, 0, 0, SRCCOPY);
		return 0;
	}

	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);

		if (flag)
		{
			switch (mode) //определение текущей фигуры
			{
			case LINE:
				draw_object = new Line;
				break;
			case RECTANGLE:
				draw_object = new Rectangles;
				break;
			case CIRCLE:
				draw_object = new Circle;
				break;
			case POINTs:
				draw_object = new Point;
				break;
			}
		}

		ButtonDown(hdc, lParam);//прорисовка фигуры, если все координаты определены

		ReleaseDC(hWnd, hdc);

		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_PENCIL:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, ColorChoise);//диалоговое окно выбора цвета контура
			pencil = palette_stack.Peek(element);//получение необходимого цвета из стека
			break;
		}

		case IDM_BRUSH:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, ColorChoise);//диалоговое окно выбора цвета заливки
			brush = palette_stack.Peek(element);//получение необходимого цвета из стека
			break;
		}

		case ID_LINE:
		{
			mode = LINE;
			break;
		}

		case ID_CIRCLE:
		{
			mode = CIRCLE;
			break;
		}

		case ID_RECTANGLE:
		{
			mode = RECTANGLE;
			break;
		}

		case ID_POINT:
		{
			mode = POINTs;
			break;
		}

		case SIZE2:
		{
			pencil_size = 2;
			break;
		}

		case SIZE4:
		{
			pencil_size = 4;
			break;
		}

		case SIZE8:
		{
			pencil_size = 8;
			break;
		}

		case SIZE16:
		{
			pencil_size = 16;
			break;
		}

		case ID_SAVE:
		{
			HDC hdc = GetDC(hWnd);

			SaveFile(hWnd, hdc);

			ReleaseDC(hWnd, hdc);
			break;
		}

		case ID_RETURN:
		{
			HDC hdc = GetDC(hWnd);

			LastState(hdc); //функция отмены последнего действия

			ReleaseDC(hWnd, hdc);

			break;
		}

		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		BitBlt(hdc, 0, 0, width, height, screen_buf, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
	}
	break;


	case WM_DESTROY:
	{
		list<Shape*>::iterator iter_shape = shape_list.begin();
		list<Painting*>::iterator iter_painting = painting_list.begin();
		int size = (int)shape_list.size();

		for (int k = 0; k < size; k++, iter_shape++, iter_painting++)
		{
			delete *iter_painting;
			delete *iter_shape;
		}

		DeleteDC(screen_buf);
		DeleteDC(screen_buf_first);

		PostQuitMessage(0);
		break;
	}
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "Выбор цвета...".
INT_PTR CALLBACK ColorChoise(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		case IDC_BLACK:
		{
			element = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		case IDC_WHITE:
		{
			element = 1;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		case IDC_RED:
		{
			element = 2;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		case IDC_GREEN:
		{
			element = 3;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		case IDC_BLUE:
		{
			element = 4;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		case IDC_CYAN:
		{
			element = 5;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		case IDC_YELLOW:
		{
			element = 6;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		case IDC_ORANGE:
		{
			element = 7;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		case IDC_PURPLE:
		{
			element = 8;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		}
		break;
	}
	break;
    }
    return (INT_PTR)FALSE;
}

void SaveFile(HWND hWnd, HDC windowDC)
{
	TCHAR szFilters[] = _T("Myfile (*.emf)\0\0");
	TCHAR szFilePathName[_MAX_PATH] = _T("");
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = szFilters;
	ofn.lpstrFile = szFilePathName; // Имя файла
	ofn.lpstrDefExt = _T("emf");
	ofn.nMaxFile = _MAX_PATH;
	ofn.lpstrTitle = _T("Save File");
	ofn.Flags = OFN_OVERWRITEPROMPT;
	ofn.lpstrInitialDir = _T("C:\\");
	
	GetSaveFileName(&ofn); // Открыть диалог сохранения файла, выбрать имя

	RECT rect;
	HGDIOBJ hOldBrush;
	HBRUSH hBrush;
	HDC hDCMeta;
	HENHMETAFILE hemf;

	GetClientRect(hWnd, &rect);
	hDCMeta = CreateEnhMetaFile(windowDC, ofn.lpstrFile, NULL, NULL);

	hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	hOldBrush = SelectObject(hDCMeta, hBrush);

	BitBlt(hDCMeta, 0, 0, rect.right, rect.bottom, windowDC, 0, 0, SRCCOPY);

	SelectObject(hDCMeta, hOldBrush);
	hemf = CloseEnhMetaFile(hDCMeta);
	DeleteEnhMetaFile(hemf);
}

void ButtonDown(HDC hdc, LPARAM lParam)
{
	flag = draw_object->ClickMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), screen_buf);
	if (flag)
	{
		flag = 0;
	}
	else
	{
		painting = new Painting;
		painting->Set(pencil, brush, pencil_size);
		painting_list.push_back(painting);

		draw_object->Draw(screen_buf, painting);
		draw_object->Draw(hdc, painting);

		shape_list.push_back(draw_object);
		flag = 1;
	}
}


void LastState(HDC hdc)
{
	list<Shape*>::iterator iter_shape = shape_list.begin();
	list<Painting*>::iterator iter_painting = painting_list.begin();
	if (shape_list.size() != 0)
	{
		BitBlt(screen_buf, 0, 0, width, height, screen_buf_first, 0, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, width, height, screen_buf_first, 0, 0, SRCCOPY);

		for (int k = 0; k < (shape_list.size() - 1); k++, iter_shape++, iter_painting++)
		{
			painting = *iter_painting;
			draw_object = *iter_shape;

			draw_object->Draw(screen_buf, painting);
			draw_object->Draw(hdc, painting);
		}

		delete *iter_painting;
		painting_list.pop_back();

		delete *iter_shape;
		shape_list.pop_back();
	}
}

void Stack_filling()
{
	//palette_stack.push(PURPLE_COLOR);
	//palette_stack.push(ORANGE_COLOR);
	//palette_stack.push(YELLOW_COLOR);
	//palette_stack.push(CYAN_COLOR);
	//palette_stack.push(BLUE_COLOR);
	//palette_stack.push(GREEN_COLOR);
	//palette_stack.push(RED_COLOR);
	//palette_stack.push(WHITE_COLOR);
	//palette_stack.push(BLACK_COLOR);
	palette_stack.Add(PURPLE_COLOR);
	palette_stack.Add(ORANGE_COLOR);
	palette_stack.Add(YELLOW_COLOR);
	palette_stack.Add(CYAN_COLOR);
	palette_stack.Add(BLUE_COLOR);
	palette_stack.Add(GREEN_COLOR);
	palette_stack.Add(RED_COLOR);
	palette_stack.Add(WHITE_COLOR);
	palette_stack.Add(BLACK_COLOR);
}
