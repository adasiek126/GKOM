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
const MaterialParameters materials[34] = MaterialParameters[34]
(
    // materia³ domyœlny, MTL_DEFAULT
    MaterialParameters( vec4( 0.2, 0.2, 0.2, 1.0 ),
                        vec4( 0.8, 0.8, 0.8, 1.0 ),
                        vec4( 0.0, 0.0, 0.0, 1.0 ),
                        0.0 ),

    // materia³ - mosi¹dz, MTL_BRASS
    MaterialParameters( vec4( 0.329412, 0.223529, 0.027451, 1.000000 ),
                        vec4( 0.780392, 0.568627, 0.113725, 1.000000 ),
                        vec4( 0.992157, 0.941176, 0.807843, 1.000000 ),
                        27.8974 ),

    // materia³ - br¹z, MTL_BRONZE
    MaterialParameters( vec4( 0.212500, 0.127500, 0.054000, 1.000000 ),
                        vec4( 0.714000, 0.428400, 0.181440, 1.000000 ),
                        vec4( 0.393548, 0.271906, 0.166721, 1.000000 ),
                        25.6 ),

    // materia³ - polerowany br¹z, MTL_POLISHED_BRONZE
    MaterialParameters( vec4( 0.250000, 0.148000, 0.064750, 1.000000 ),
                        vec4( 0.400000, 0.236800, 0.103600, 1.000000 ),
                        vec4( 0.774597, 0.458561, 0.200621, 1.000000 ),
                        76.8 ),

    // materia³ - chrom, MTL_CHROME
    MaterialParameters( vec4( 0.250000, 0.250000, 0.250000, 1.000000 ),
                        vec4( 0.400000, 0.400000, 0.400000, 1.000000 ),
                        vec4( 0.774597, 0.774597, 0.774597, 1.000000 ),
                        76.8 ),

    // materia³ - miedŸ, MTL_COPPER
    MaterialParameters( vec4( 0.191250, 0.073500, 0.022500, 1.000000 ),
                        vec4( 0.703800, 0.270480, 0.082800, 1.000000 ),
                        vec4( 0.256777, 0.137622, 0.086014, 1.000000 ),
                        12.8 ),

    // materia³ - polerowana miedŸ, MTL_POLISHED_COPPER
    MaterialParameters( vec4( 0.229500, 0.088250, 0.027500, 1.000000 ),
                        vec4( 0.550800, 0.211800, 0.066000, 1.000000 ),
                        vec4( 0.580594, 0.223257, 0.069570, 1.000000 ),
                        51.2 ),

    // materia³ - z³oto, MTL_GOLD
    MaterialParameters( vec4( 0.247250, 0.199500, 0.074500, 1.000000 ),
                        vec4( 0.751640, 0.606480, 0.226480, 1.000000 ),
                        vec4( 0.628281, 0.555802, 0.366065, 1.000000 ),
                        52.2 ),

    // materia³ - polerowane z³oto, MTL_POLISHED_GOLD
    MaterialParameters( vec4( 0.247250, 0.224500, 0.064500, 1.000000 ),
                        vec4( 0.346150, 0.314300, 0.090300, 1.000000 ),
                        vec4( 0.797357, 0.723991, 0.208006, 1.000000 ),
                        83.2 ),

    // materia³ - grafit (cyna z o³owiem), MTL_PEWTER
    MaterialParameters( vec4( 0.105882, 0.058824, 0.113725, 1.000000 ),
                        vec4( 0.427451, 0.470588, 0.541176, 1.000000 ),
                        vec4( 0.333333, 0.333333, 0.521569, 1.000000 ),
                        9.84615 ),

    // materia³ - srebro, MTL_SILVER,
    MaterialParameters( vec4( 0.192250, 0.192250, 0.192250, 1.000000 ),
                        vec4( 0.507540, 0.507540, 0.507540, 1.000000 ),
                        vec4( 0.508273, 0.508273, 0.508273, 1.000000 ),
                        51.2 ),

    // materia³ - polerowane srebro, MTL_POLISHED_SILVER
    MaterialParameters( vec4( 0.231250, 0.231250, 0.231250, 1.000000 ),
                        vec4( 0.277500, 0.277500, 0.277500, 1.000000 ),
                        vec4( 0.773911, 0.773911, 0.773911, 1.000000 ),
                        89.6 ),

    // materia³ - szmaragd, MTL_EMERALD
    MaterialParameters( vec4( 0.021500, 0.174500, 0.021500, 0.550000 ),
                        vec4( 0.075680, 0.614240, 0.075680, 0.550000 ),
                        vec4( 0.633000, 0.727811, 0.633000, 0.550000 ),
                        76.8 ),

    // materia³ - jadeit, MTL_JADE
    MaterialParameters( vec4( 0.135000, 0.222500, 0.157500, 0.950000 ),
                        vec4( 0.540000, 0.890000, 0.630000, 0.950000 ),
                        vec4( 0.316228, 0.316228, 0.316228, 0.950000 ),
                        12.8 ),

    // materia³ - obsydian (szk³o wulkaniczne), MTL_OBSIDIAN
    MaterialParameters( vec4( 0.053750, 0.050000, 0.066250, 0.820000 ),
                        vec4( 0.182750, 0.170000, 0.225250, 0.820000 ),
                        vec4( 0.332741, 0.328634, 0.346435, 0.820000 ),
                        38.4 ),

    // materia³ - per³a, MTL_PEARL
    MaterialParameters( vec4( 0.250000, 0.207250, 0.207250, 0.922000 ),
                        vec4( 1.000000, 0.829000, 0.829000, 0.922000 ),
                        vec4( 0.296648, 0.296648, 0.296648, 0.922000 ),
                        11.264 ),

    // metaria³ - rubin, MTL_RUBY
    MaterialParameters( vec4( 0.174500, 0.011750, 0.011750, 0.550000 ),
                        vec4( 0.614240, 0.041360, 0.041360, 0.550000 ),
                        vec4( 0.727811, 0.626959, 0.626959, 0.550000 ),
                        76.8 ),

    // materia³ - turkus, MTL_TURQUOISE
    MaterialParameters( vec4( 0.100000, 0.187250, 0.174500, 0.800000 ),
                        vec4( 0.396000, 0.741510, 0.691020, 0.800000 ),
                        vec4( 0.297254, 0.308290, 0.306678, 0.800000 ),
                        12.8 ),

    // materia³ - jasny bia³y, MTL_BRIGHT_WHITE
    MaterialParameters( vec4( 0.2, 0.2, 0.2, 1.000000 ),
                        vec4( 1.0, 1.0, 1.0, 1.000000 ),
                        vec4( 0.8, 0.8, 0.8, 1.000000 ),
                        51.2 ),

    // materia³ -  mniej jasny bia³y, MTL_LESS_BRIGHT_WHITE
    MaterialParameters( vec4( 0.2, 0.2, 0.2, 1.000000 ),
                        vec4( 0.8, 0.8, 0.8, 1.000000 ),
                        vec4( 0.5, 0.5, 0.5, 1.000000 ),
                        44.8 ),

    // materia³ - ciep³y bia³y, MTL_WARMISH_WHITE
    MaterialParameters( vec4( 0.3, 0.2, 0.2, 1.000000 ),
                        vec4( 1.0, 0.9, 0.8, 1.000000 ),
                        vec4( 0.4, 0.2, 0.2, 1.000000 ),
                        44.8 ),

    // materia³ - zimny bia³y, MTL_COOLISH_WHITE
    MaterialParameters( vec4( 0.2, 0.2, 0.3, 1.000000 ),
                        vec4( 0.8, 0.9, 1.0, 1.000000 ),
                        vec4( 0.2, 0.2, 0.4, 1.000000 ),
                        44.8 ),

    // materia³ - czarny plastik, MTL_BLACK_PLASTIC
    MaterialParameters( vec4( 0.000000, 0.000000, 0.000000, 1.000000 ),
                        vec4( 0.010000, 0.010000, 0.010000, 1.000000 ),
                        vec4( 0.500000, 0.500000, 0.500000, 1.000000 ),
                        32.0 ),

    // materia³ - niebieskozielony plastik, MTL_CYAN_PLASTIC
    MaterialParameters( vec4( 0.0, 0.1, 0.06, 1.000000 ),
                        vec4( 0.0, 0.50980392, 0.50980392, 1.000000 ),
                        vec4( 0.50196078, 0.50196078, 0.50196078, 1.000000 ),
                        32.0 ),

    // materia³ - zielony plastik, MTL_GREEN_PLASTIC
    MaterialParameters( vec4( 0.0, 0.0, 0.0, 1.000000 ),
                        vec4( 0.1, 0.35, 0.1, 1.000000 ),
                        vec4( 0.45, 0.55, 0.45, 1.000000 ),
                        32.0 ),

    // materia³ - czerwony plastik, MTL_RED_PLASTIC
    MaterialParameters( vec4( 0.0, 0.0, 0.0, 1.000000 ),
                        vec4( 0.5, 0.0, 0.0, 1.000000 ),
                        vec4( 0.7, 0.6, 0.6, 1.000000 ),
                        32.0 ),

    // materia³ - bia³y plastik, MTL_WHITE_PLASTIC
    MaterialParameters( vec4( 0.0, 0.0, 0.0, 1.000000 ),
                        vec4( 0.55, 0.55, 0.55, 1.000000 ),
                        vec4( 0.70, 0.70, 0.70, 1.000000 ),
                        32.0 ),

    // materia³ - ¿ó³ty plastik, MTL_YELLOW_PLASTIC
    MaterialParameters( vec4( 0.0, 0.0, 0.0,  1.000000 ),
                        vec4( 0.5, 0.5, 0.0, 1.000000 ),
                        vec4( 0.60, 0.60, 0.50, 1.000000 ),
                        32.0 ),

    // materia³ - czarna guma, MTL_BLACK_RUBBER
    MaterialParameters( vec4( 0.020000, 0.020000, 0.020000, 1.000000 ),
                        vec4( 0.010000, 0.010000, 0.010000, 1.000000 ),
                        vec4( 0.040000, 0.040000, 0.040000, 1.000000 ),
                        10.0 ),

    // materia³ - niebieskozielona guma, MTL_CYAN_RUBBER
    MaterialParameters( vec4( 0.0, 0.05, 0.05, 1.000000 ),
                        vec4( 0.4, 0.5, 0.5, 1.000000 ),
                        vec4( 0.04, 0.7, 0.7, 1.000000 ),
                        10.0 ),

    // materia³ - zielona guma, MTL_GREEN_RUBBER
    MaterialParameters( vec4( 0.0, 0.05, 0.0, 1.000000 ),
                        vec4( 0.4, 0.5, 0.4, 1.000000 ),
                        vec4( 0.04, 0.7, 0.04, 1.000000 ),
                        10.0 ),

    // materia³ - czerwona guma, MTL_RED_RUBBER
    MaterialParameters( vec4( 0.05, 0.0, 0.0, 1.000000 ),
                        vec4( 0.5, 0.4, 0.4, 1.000000 ),
                        vec4( 0.7, 0.04, 0.04, 1.000000 ),
                        10.0 ),

    // materia³ - bia³a guma, MTL_WHITE_RUBBER
    MaterialParameters( vec4( 0.05, 0.05, 0.05, 1.000000 ),
                        vec4( 0.5, 0.5, 0.5, 1.000000 ),
                        vec4( 0.7, 0.7, 0.7, 1.000000 ),
                        10.0 ),

    // materia³ - ¿ó³ta guma, MTL_YELLOW_RUBBER
    MaterialParameters( vec4( 0.05, 0.05, 0.0, 1.000000 ),
                        vec4( 0.5, 0.5, 0.4, 1.000000 ),
                        vec4( 0.7, 0.7, 0.04, 1.000000 ),
                        10.0 )
);

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
