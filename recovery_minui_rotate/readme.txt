revovery minui�ṩ��һ�ֶԳ�����ϵͳ��Android/linux������һ�ֲ�����ʾ�豸
fb�Ļ�ͼ������

�ṩ��һЩ�򵥵Ļ�ͼ���ߣ���ϸ�ο�\bootable\recovery\minui\��
void gr_clear();  // clear entire surface to current color
void gr_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void gr_fill(int x1, int y1, int x2, int y2);
void gr_text(int x, int y, const char *s, int bold);
void gr_texticon(int x, int y, gr_surface icon);
int gr_measure(const char *s);
void gr_font_size(int *x, int *y);

// Resources

// res_create_*_surface() functions return 0 if no error, else
// negative.
//
// A "display" surface is one that is intended to be drawn to the
// screen with gr_blit().  An "alpha" surface is a grayscale image
// interpreted as an alpha mask used to render text in the current
// color (with gr_text() or gr_texticon()).
//
// All these functions load PNG images from "/res/images/${name}.png".

// Load a single display surface from a PNG image.
int res_create_display_surface(const char* name, gr_surface* pSurface);

// Load an array of display surfaces from a single PNG image.  The PNG
// should have a 'Frames' text chunk whose value is the number of
// frames this image represents.  The pixel data itself is interlaced
// by row.
int res_create_multi_display_surface(const char* name,
                                     int* frames, gr_surface** pSurface);

// Load a single alpha surface from a grayscale PNG image.
int res_create_alpha_surface(const char* name, gr_surface* pSurface);

// Load part of a grayscale PNG image that is the first match for the
// given locale.  The image is expected to be a composite of multiple
// translations of the same text, with special added rows that encode
// the subimages' size and intended locale in the pixel data.  See
// development/tools/recovery_l10n for an app that will generate these
// specialized images from Android resources.
int res_create_localized_alpha_surface(const char* name, const char* locale,
                                       gr_surface* pSurface);
                                       
�������ﲢû�и�����fb����buffer����ת���������Դ����и�����һ��diff�ļ�����ϸ���룬
����ʵ��fb��ת90,180,270�Ĳ�����ʵ�ֳ��ͼ���recovery������ת�Ĺ��ܡ�