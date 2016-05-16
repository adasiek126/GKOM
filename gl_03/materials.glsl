//////////////////////////////////////////////////////////////////////
// (c) Janusz Ganczarski
// http://www.januszg.hg.pl
// JanuszG@enter.net.pl
//////////////////////////////////////////////////////////////////////
// Ÿród³o danych:
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
// struktura opisuj¹ca parametry materia³u
//////////////////////////////////////////////////////////////////////
struct MaterialParameters
{
    vec4 ambient;       // wspó³czynnik odbicia œwiat³a otoczenia; oznaczenie Ma
    vec4 diffuse;       // wspó³czynnik odbicia œwiat³a rozproszonego; oznaczenie Md
    vec4 specular;      // wspó³czynnik odbicia œwiat³a zwierciadlanego; oznaczenie Ms
    float shininess;    // wyk³adnik wspó³czynnika funkcji rozb³ysku;
                        // zakres wartoœci <0;128>; oznaczenie Msh
};

//////////////////////////////////////////////////////////////////////
// sta³e okreœlaj¹ce poszczególne materia³y
//////////////////////////////////////////////////////////////////////
#define MTL_DEFAULT              0  // materia³ domyœlny
#define MTL_BRASS                1  // mosi¹dz
#define MTL_BRONZE               2  // br¹z
#define MTL_POLISHED_BRONZE      3  // polerowany br¹z
#define MTL_CHROME               4  // chrom
#define MTL_COPPER               5  // miedŸ
#define MTL_POLISHED_COPPER      6  // polerowana miedŸ
#define MTL_GOLD                 7  // z³oto
#define MTL_POLISHED_GOLD        8  // polerowane z³oto
#define MTL_PEWTER               9  // grafit (cyna z o³owiem)
#define MTL_SILVER              10  // srebro
#define MTL_POLISHED_SILVER     11  // polerowane srebro
#define MTL_EMERALD             12  // szmaragd
#define MTL_JADE                13  // jadeit
#define MTL_OBSIDIAN            14  // obsydian (szk³o wulkaniczne)
#define MTL_PEARL               15  // per³a
#define MTL_RUBY                16  // rubin
#define MTL_TURQUOISE           17  // turkus
#define MTL_BRIGHT_WHITE        18  // jasny bia³y
#define MTL_LESS_BRIGHT_WHITE   19  // mniej jasny bia³y
#define MTL_WARMISH_WHITE       20  // ciep³y bia³y
#define MTL_COOLISH_WHITE       21  // zimny bia³y
#define MTL_BLACK_PLASTIC       22  // czarny plastik
#define MTL_CYAN_PLASTIC        23  // niebieskozielony plastik
#define MTL_GREEN_PLASTIC       24  // zielony plastik
#define MTL_RED_PLASTIC         25  // czerwony plastik
#define MTL_WHITE_PLASTIC       26  // bia³y plastik
#define MTL_YELLOW_PLASTIC      27  // ¿ó³ty plastik
#define MTL_BLACK_RUBBER        28  // czarna guma
#define MTL_CYAN_RUBBER         29  // niebieskozielona guma
#define MTL_GREEN_RUBBER        30  // zielona guma
#define MTL_RED_RUBBER          31  // czerwona guma
#define MTL_WHITE_RUBBER        32  // bia³a guma
#define MTL_YELLOW_RUBBER       33  // ¿ó³ta guma

//////////////////////////////////////////////////////////////////////
// dane poszczególnych materia³ów
//////////////////////////////////////////////////////////////////////
layout( std140 ) uniform Materials
{
     MaterialParameters materials[34];
};

//////////////////////////////////////////////////////////////////////
// pobranie okreœlonego materia³u
//////////////////////////////////////////////////////////////////////
MaterialParameters GetMaterial( const int material )
{
    if( material >= MTL_DEFAULT && material <= MTL_YELLOW_RUBBER )
        return materials[material];
    else
        return materials[MTL_DEFAULT];
}
