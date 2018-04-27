#include <fcntl.h> 
#include <io.h>   
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
struct sinhvien
{
	wchar_t MSSV[10];
	wchar_t hoten[30];
	wchar_t khoa[30];
	int khoas;
	wchar_t gmail[50];
	wchar_t ngaysinh[20];
	wchar_t hinhanh[50];
	wchar_t mota[100];
	wchar_t sothich[10][100];
};
void bodau(wchar_t a[], int i)
{
	int l = wcslen(a);
	for (int j = i; j < l - 1; j++)
	{
		a[j] = a[j + 1];
	}
	a[l - 1] = '\0';
}
void tachso(FILE *input, int &n)
{
	wchar_t c = fgetwc(input);
	if (c == '"')
	{
		fwscanf_s(input, L"%d", &n);
		fseek(input, 2L, SEEK_CUR);
	}
	else
	{
		fseek(input, -1L, SEEK_CUR);
		fwscanf_s(input, L"%d", &n);
		fseek(input, 1L, SEEK_CUR);
	}
}
void tach(FILE *input, wchar_t b[])
{
	int i = 0;
	wchar_t c = fgetwc(input);
	if (c == '"')
	{
		c = fgetwc(input);
		while (1)
		{
			if (c == '"' || c == EOF)
			{
				break;
			}
			b[i] = c;
			i++;
			c = fgetwc(input);
		}
		b[i] = '\0';
		fgetwc(input);
	}
	else
	{
		while (1)
		{
			if (c == ',' || c == EOF || c == '\n')
			{
				break;
			}
			b[i] = c;
			i++;
			c = fgetwc(input);
		}
		b[i] = '\0';
	}
}
void inut(FILE *input, sinhvien &a, int &i)
{
	tach(input, a.MSSV);
	tach(input, a.hoten);
	tach(input, a.ngaysinh);
	tach(input, a.khoa);
	tachso(input, a.khoas);
	tach(input, a.gmail);
	tach(input, a.hinhanh);
	tach(input, a.mota);
	wchar_t temp[256];
	fgetws(temp, 256, input);
	wprintf(L"%s\n", temp);
	wchar_t *kt = wcstok(temp, L",");
	i = 0;
	while (kt != NULL)
	{
		int l = wcslen(kt);
		for (int j = 0; j < l; j++)
		{
			a.sothich[i][j] = kt[j];
		}
		a.sothich[i][l] = '\0';
		int x = wcslen(a.sothich[i]);
		if (a.sothich[i][x - 1] == '"')
		{
			a.sothich[i][x - 1] = '\0';
		}
		for (int j = 0; j < wcslen(a.sothich[i]); j++)
		{
			if (a.sothich[i][j] == '"')
			{
				bodau(a.sothich[i], j);
			}
		}
		i++;
		kt = wcstok(NULL, L",");
	}
}
int kt(int b[], int l, int i)
{
	for (int j = 0; j < l; j++)
	{
		if (b[j] == i)
		{
			return 1;
		}
	}
	return 0;
}
int dem(FILE *input)
{
	int i = 0;
	wchar_t temp[256];
	wchar_t *temp2;
	while ((temp2 = fgetws(temp, 256, input)) != NULL)
	{
		i++;
	}
	rewind(input);
	return i;
}
void menu2(sinhvien a[], int b[], int &i, int h)
{
	system("cls");
	wprintf(L"\t\t LỰA CHỌN \n");
	int n;
	wprintf(L"\n\t*LỰA CHỌN SINH VIÊN BẠN MUỐN TẠO TRANG*\n\n");
	for (int k = 0; k < h; k++)
	{
		wprintf(L"%d.%s\n", k + 1, a[k].hoten);
	}
	wprintf(L"11.Tất Cả\n");
	wprintf(L"0.Kết Thúc\n\n");
	while (1)
	{
		int dem = 0;
		wprintf(L"\tNhập Lựa Chọn: ");
		wscanf_s(L"%d", &n);

		if (n == 0)
		{
			wprintf(L"\n\n\t\t\t\t\tKết thúc quá trình lựa chọn!\n\t\t\t\t\t\tTHANK YOU\n");
			break;
		}
		if (n == 11)
		{
			wprintf(L"\n\tBạn Đã Lựa Chọn Hiển Thị Tất Cả Thông Tin");
			b[i] = n;
			i++;
			break;
		}
		for (int j = 0; j < i; j++)
		{
			if (n == b[j])
			{
				dem++;
			}
		}
		if (dem != 0)
		{
			wprintf(L"\n\n\t******!!!Lựa Chọn Đã Được Nhập!!!******\n\t   ******!!!Vui Lòng chọn Lại!!!******\n\n");
			continue;
		}
		b[i] = n;
		i++;
	}
	_getch();
}
void menu(sinhvien a, int b[10], int &i, int j)
{
	i = 0;
	system("cls");
	wprintf(L"\n\t\tHọc Sinh  :%s  \n", a.hoten);
	int n;
	wprintf(L"\n\t*LỰA CHỌN THÔNG TIN CỦA SINH VIÊN BẠN MUỐN HIỂN THỊ*\n\n");
	wprintf(L"1.MSSV\n");
	wprintf(L"2.Họ Tên\n");
	wprintf(L"3.Ngày Sinh\n");
	wprintf(L"4.Khoa\n");
	wprintf(L"5.Khóa\n");
	wprintf(L"6.Mô Tả\n");
	wprintf(L"7.Sở Thích\n");
	wprintf(L"8.Tất Cả\n");
	wprintf(L"0.Kết Thúc\n\n");
	while (1)
	{
		int dem = 0;
		wprintf(L"\tNhập Lựa Chọn: ");
		wscanf_s(L"%d", &n);

		if (n == 0)
		{
			wprintf(L"\n\n\t\t\t\t\tKết thúc quá trình lựa chọn!\n\t\t\t\t\t\tTHANK YOU\n");
			break;
		}
		if (n == 9)
		{
			wprintf(L"\n\tBạn Đã Lựa Chọn Hiển Thị Tất Cả Thông Tin");
			b[i] = n;
			i++;
			break;
		}
		for (int j = 0; j < i; j++)
		{
			if (n == b[j])
			{
				dem++;
			}
		}
		if (dem != 0)
		{
			wprintf(L"\n\n\t******!!!Lựa Chọn Đã Được Nhập!!!******\n\t   ******!!!Vui Lòng chọn Lại!!!******\n\n");
			continue;
		}
		b[i] = n;
		i++;
	}
	_getch();
}
void ouput(FILE *output, sinhvien a, int b[10], int l, int i)
{
	fwprintf(output, L"      <!DOCTYPE html PUBLIC \" -//W3C//DTD XHTML 1.0 Transitional//EN\" ");
	fwprintf(output, L" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd \">\n");
	fwprintf(output, L" <html xmlns=\"http://www.w3.org/1999/xhtml \">\n");
	fwprintf(output, L"<head>\n");
	fwprintf(output, L"<meta http-equiv=\"Conten-Type\" content=\"text/html; charset=utf - 8\" />\n");
	fwprintf(output, L"<link rel=\"stylesheet\" type=\"text/css\" href=\"personal.css\" />\n");
	fwprintf(output, L"<title>%s</title>\n", a.hoten);
	fwprintf(output, L"</head>\n<body>\n<div class=\"Layout_container\">\n");
	fwprintf(output, L"            <!-- Begin Layout Banner Region -->\n");
	fwprintf(output, L"<div class=\"Layout_Banner\" >\n");
	fwprintf(output, L"<div><img id=\"logo\" src=\"Images/logo.jpg\" height=\"105\" /></div>\n");
	fwprintf(output, L"<div class=\"Header_Title\">Khoa Học Tự Nhiên </div>\n");
	fwprintf(output, L"</div>\n<!--End Layout Banner Region-->\n<!--Begin Layout MainContents Region-->\n");
	fwprintf(output, L"<div class=\"Layout_MainContents\">\n<!--Begin Below Banner Region-->\n<div class=\"Personal_Main_Information\">\n");
	fwprintf(output, L"<!-- Begin Thông tin cá nhân c?a th?y cô ----------------------------------------------------------------------------------------- -->\n<div class=\"Personal_Location\">\n");
	fwprintf(output, L"<img src=\"Images/LogoFooter.jpg\" width=\"27\" height=\"33\" />\n");

	if (kt(b, l, 1) == 1 || kt(b, l, 2) == 1 || kt(b, l, 9) == 1)
	{
		fwprintf(output, L"<div class=\"Personal_FullName\">%s - %s</div>\n", a.hoten, a.MSSV);
	}

	if (kt(b, l, 4) == 1 || kt(b, l, 9) == 1)
	{
		fwprintf(output, L"<div class=\"Personal_Department\">%s</div>\n", a.khoa);
	}
	fwprintf(output, L"<br />\n<div class=\"Personal_Phone\">\n");
	fwprintf(output, L"Email: %s\n</div>\n<br />\n", a.gmail);
	fwprintf(output, L"                        <br />   \n                 </div>\n<!--End Thông tin cá nhân c ? a th ? y cô---------------------------------------------------------------------------------------- - -->\n");
	fwprintf(output, L"<div class=\"Personal_HinhcanhanKhung\">\n<img src=\"Images/%s.jpg\" class=\"Personal_Hinhcanhan\" />\n</div>\n</div>\n", a.hinhanh);
	fwprintf(output, L"<!-- End Below Banner Region -->\n<!--Begin MainContents Region-->\n<div class=\"MainContain\">\n\n");
	fwprintf(output, L"<!-- Begin Top Region -->\n<div class=\"MainContain_Top\">\n\n<div class=\"InfoGroup\">Thông tin cá nhân</div>\n<div>\n");
	fwprintf(output, L"<ul class=\"TextInList\">\n");
	if (kt(b, l, 2) == 1 || kt(b, l, 9) == 1)
	{
		fwprintf(output, L"<li>Họ và tên :%s</li>\n", a.hoten);
	}
	if (kt(b, l, 1) == 1 || kt(b, l, 9) == 1)
	{
		fwprintf(output, L"<li>MSSV : %s</li>\n", a.MSSV);
	}
	if (kt(b, l, 4) == 1 || kt(b, l, 9) == 1)
	{
		fwprintf(output, L"<li>Sinh viên khoa :  %s</li>\n", a.khoa);
	}
	if (kt(b, l, 3) == 1 || kt(b, l, 9) == 1)
	{
		fwprintf(output, L"<li>Ngày sinh : %s</li>\n", a.ngaysinh);
	}
	fwprintf(output, L"<li>Email : %s</li>\n", a.gmail);
	fwprintf(output, L"</ul>\n </div>\n");
	fwprintf(output, L"<div class=\"InfoGroup\">Sở thích</div>\n<div>\n<ul class=\"TextInList\">\n");
	if (kt(b, l, 8) == 1 || kt(b, l, 9) == 1)
	{
		for (int j = 0; j < i; j++)
		{
			fwprintf(output, L"<li>Sở Thích %d : %s</li>\n", j + 1, a.sothich[j]);
		}
	}
	fwprintf(output, L"                            </ul>\n</div>\n<div class=\"InfoGroup\">Mô tả</div>\n<div class=\"Description\">\n");
	if (kt(b, l, 7) == 1 || kt(b, l, 9) == 1)
	{
		fwprintf(output, L"%s\n", a.mota);
	}
	fwprintf(output, L"</div>   \n                     </div>\n</div>\n</div>\n\n<!--Begin Layout Footer-->\n");
	fwprintf(output, L"            <div class=\"Layout_Footer\">\n<div class=\"divCopyright\">\n<br />\n");
	fwprintf(output, L"<img src=\"Images/LogoFooter_gray.jpg\" width=\"34\" height=\"41\" /><br />\n<br />\n@2013</br>\nĐồ án giữ kỳ</br>\nKỹ thuật lập trình</br>\n");
	fwprintf(output, L"                TH2012/03</br>\n1712918 - Hoàng Minh Vũ</br>\n</div>\n</div>\n<!--End Layout Footer-->\n");
	fwprintf(output, L"        </div>\n</body>\n</html>\n");
	fwprintf(output, L"<li>\n\n\n\n\n\n</li>\n");
}
void main()
{
	sinhvien a[20];
	int  b[10][20], l[10], i[20], c[20], k = 0;
	_setmode(_fileno(stdout), _O_U8TEXT);
	FILE* input = _wfopen(L"input.csv", L"r, ccs=UTF-8");
	if (!input)
	{
		wprintf(L"Không nhận đc file!!!");
		return;
	}
	_setmode(_fileno(input), _O_U8TEXT);
	int h = dem(input);
	for (int j = 0; j < h; j++)
	{

		inut(input, a[j], i[j]);
	}
	menu2(a, c, k, h);
	for (int j = 0; j < h; j++)
	{
		for (int q = 0; q < k; q++)
		{
			if (c[q] == j + 1 || c[q] == 11)
			{
				menu(a[j], b[j], l[j], j + 1);
			}
		}
	}
	fclose(input);
	wchar_t s[30];
	wchar_t *s1;
	wchar_t *s2 = L".htm";
	for (int j = 0; j < h; j++)
	{
		wcscpy(s, a[j].MSSV);
		s1 = s;
		wcscat(s1, s2);
		for (int q = 0; q < k; q++)
		{
			if (c[q] == j + 1 || c[q] == 11)
			{
				FILE*output = _wfopen(s1, L"w, ccs=UTF-8");
				if (!output)
				{
					wprintf(L"không tạo đc !!!");
					return;
				}

				ouput(output, a[j], b[j], l[j], i[j]);
				fclose(output);
			}
		}
	}
	_getch();
}

