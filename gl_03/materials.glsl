//////////////////////////////////////////////////////////////////////
// (c) Janusz Ganczarski
// http://www.januszg.hg.pl
// JanuszG@enter.net.pl
//////////////////////////////////////////////////////////////////////
// �r�d�o danych:
// Advanced Graphics Programming Techniques Using OpenGL
// SIGGRAPH `99 Course
// http://www.opengl.org/resources/code/samples/sig99/advanced99/notes/node153.html
// oraz:
// http://www.sc.ehu.es/ccwgamoa/docencia/Material/OpenGL/Materials-Parameters/materials_cpp_values.html
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// GLSL 1.50
//////////////////////////////////////////////////////////////////////
#version 150

//////////////////////////////////////////////////////////////////////
// struktura opisuj�ca parametry materia�u
//////////////////////////////////////////////////////////////////////
struct MaterialParameters
{
    vec4 ambient;       // wsp�czynnik odbicia �wiat�a otoczenia; oznaczenie Ma
    vec4 diffuse;       // wsp�czynnik odbicia �wiat�a rozproszonego; oznaczenie Md
    vec4 specular;      // wsp�czynnik odbicia �wiat�a zwierciadlanego; oznaczenie Ms
    float shininess;    // wyk�adnik wsp�czynnika funkcji rozb�ysku;
                        // zakres warto�ci <0;128>; oznaczenie Msh
};

//////////////////////////////////////////////////////////////////////
// sta�e okre�laj�ce poszczeg�lne materia�y
//////////////////////////////////////////////////////////////////////
#define MTL_DEFAULT              0  // materia� domy�lny
#define MTL_BRASS                1  // mosi�dz
#define MTL_BRONZE               2  // br�z
#define MTL_POLISHED_BRONZE      3  // polerowany br�z
#define MTL_CHROME               4  // chrom
#define MTL_COPPER               5  // mied�
#define MTL_POLISHED_COPPER      6  // polerowana mied�
#define MTL_GOLD                 7  // z�oto
#define MTL_POLISHED_GOLD        8  // polerowane z�oto
#define MTL_PEWTER               9  // grafit (cyna z o�owiem)
#define MTL_SILVER              10  // srebro
#define MTL_POLISHED_SILVER     11  // polerowane srebro
#define MTL_EMERALD             12  // szmaragd
#define MTL_JADE                13  // jadeit
#define MTL_OBSIDIAN            14  // obsydian (szk�o wulkaniczne)
#define MTL_PEARL               15  // per�a
#define MTL_RUBY                16  // rubin
#define MTL_TURQUOISE           17  // turkus
#define MTL_BRIGHT_WHITE        18  // jasny bia�y
#define MTL_LESS_BRIGHT_WHITE   19  // mniej jasny bia�y
#define MTL_WARMISH_WHITE       20  // ciep�y bia�y
#define MTL_COOLISH_WHITE       21  // zimny bia�y
#define MTL_BLACK_PLASTIC       22  // czarny plastik
#define MTL_CYAN_PLASTIC        23  // niebieskozielony plastik
#define MTL_GREEN_PLASTIC       24  // zielony plastik
#define MTL_RED_PLASTIC         25  // czerwony plastik
#define MTL_WHITE_PLASTIC       26  // bia�y plastik
#define MTL_YELLOW_PLASTIC      27  // ��ty plastik
#define MTL_BLACK_RUBBER        28  // czarna guma
#define MTL_CYAN_RUBBER         29  // niebieskozielona guma
#define MTL_GREEN_RUBBER        30  // zielona guma
#define MTL_RED_RUBBER          31  // czerwona guma
#define MTL_WHITE_RUBBER        32  // bia�a guma
#define MTL_YELLOW_RUBBER       33  // ��ta guma

//////////////////////////////////////////////////////////////////////
// dane poszczeg�lnych materia��w
//////////////////////////////////////////////////////////////////////
layout( std140 ) uniform Materials
{
     MaterialParameters materials[34];
};

//////////////////////////////////////////////////////////////////////
// pobranie okre�lonego materia�u
//////////////////////////////////////////////////////////////////////
MaterialParameters GetMaterial( const int material )
{
    if( material >= MTL_DEFAULT && material <= MTL_YELLOW_RUBBER )
        return materials[material];
    else
        return materials[MTL_DEFAULT];
}
