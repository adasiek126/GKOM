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

#ifndef __MATERIALS__H__
#define __MATERIALS__H__
#include <GL/glew.h>
//////////////////////////////////////////////////////////////////////
// mosi¹dz
//////////////////////////////////////////////////////////////////////

const GLfloat mtlBrassAmbient [4] =
{
    0.329412f, 0.223529f, 0.027451f, 1.000000f
};

const GLfloat mtlBrassDiffuse [4] =
{
    0.780392f, 0.568627f, 0.113725f, 1.000000f
};

const GLfloat mtlBrassSpecular [4] =
{
    0.992157f, 0.941176f, 0.807843f, 1.000000f
};

const GLfloat mtlBrassShininess = 27.8974f;

//////////////////////////////////////////////////////////////////////
// br¹z
//////////////////////////////////////////////////////////////////////

const GLfloat mtlBronzeAmbient [4] =
{
    0.212500f, 0.127500f, 0.054000f, 1.000000f
};

const GLfloat mtlBronzeDiffuse [4] =
{
    0.714000f, 0.428400f, 0.181440f, 1.000000f
};

const GLfloat mtlBronzeSpecular [4] =
{
    0.393548f, 0.271906f, 0.166721f, 1.000000f
};

const GLfloat mtlBronzeShininess = 25.6f;

//////////////////////////////////////////////////////////////////////
// polerowany br¹z
//////////////////////////////////////////////////////////////////////

const GLfloat mtlPolishedBronzeAmbient [4] =
{
    0.250000f, 0.148000f, 0.064750f, 1.000000f
};

const GLfloat mtlPolishedBronzeDiffuse [4] =
{
    0.400000f, 0.236800f, 0.103600f, 1.000000f
};

const GLfloat mtlPolishedBronzeSpecular [4] =
{
    0.774597f, 0.458561f, 0.200621f, 1.000000f
};

const GLfloat mtlPolishedBronzeShininess = 76.8f;

//////////////////////////////////////////////////////////////////////
// chrom
//////////////////////////////////////////////////////////////////////

const GLfloat mtlChromeAmbient [4] =
{
    0.250000f, 0.250000f, 0.250000f, 1.000000f
};

const GLfloat mtlChromeDiffuse [4] =
{
    0.400000f, 0.400000f, 0.400000f, 1.000000f
};

const GLfloat mtlChromeSpecular [4] =
{
    0.774597f, 0.774597f, 0.774597f, 1.000000f
};

const GLfloat mtlChromeShininess = 76.8f;

//////////////////////////////////////////////////////////////////////
// miedŸ
//////////////////////////////////////////////////////////////////////

const GLfloat mtlCopperAmbient [4] =
{
    0.191250f, 0.073500f, 0.022500f, 1.000000f
};

const GLfloat mtlCopperDiffuse [4] =
{
    0.703800f, 0.270480f, 0.082800f, 1.000000f
};

const GLfloat mtlCopperSpecular [4] =
{
    0.256777f, 0.137622f, 0.086014f, 1.000000f
};

const GLfloat mtlCopperShininess = 12.8f;

//////////////////////////////////////////////////////////////////////
// polerowana miedŸ
//////////////////////////////////////////////////////////////////////

const GLfloat mtlPolishedCopperAmbient [4] =
{
    0.229500f, 0.088250f, 0.027500f, 1.000000f
};

const GLfloat mtlPolishedCopperDiffuse [4] =
{
    0.550800f, 0.211800f, 0.066000f, 1.000000f
};

const GLfloat mtlPolishedCopperSpecular [4] =
{
    0.580594f, 0.223257f, 0.069570f, 1.000000f
};

const GLfloat mtlPolishedCopperShininess = 51.2f;

//////////////////////////////////////////////////////////////////////
// z³oto
//////////////////////////////////////////////////////////////////////

const GLfloat mtlGoldAmbient [4] =
{
    0.247250f, 0.199500f, 0.074500f, 1.000000f
};

const GLfloat mtlGoldDiffuse [4] =
{
    0.751640f, 0.606480f, 0.226480f, 1.000000f
};

const GLfloat mtlGoldSpecular [4] =
{
    0.628281f, 0.555802f, 0.366065f, 1.000000f
};

const GLfloat mtlGoldShininess = 52.2f;

//////////////////////////////////////////////////////////////////////
// polerowane z³oto
//////////////////////////////////////////////////////////////////////

const GLfloat mtlPolishedGoldAmbient [4] =
{
    0.247250f, 0.224500f, 0.064500f, 1.000000f
};

const GLfloat mtlPolishedGoldDiffuse [4] =
{
    0.346150f, 0.314300f, 0.090300f, 1.000000f
};

const GLfloat mtlPolishedGoldSpecular [4] =
{
    0.797357f, 0.723991f, 0.208006f, 1.000000f
};

const GLfloat mtlPolishedGoldShininess = 83.2f;

//////////////////////////////////////////////////////////////////////
// cyna z o³owiem (grafit)
//////////////////////////////////////////////////////////////////////

const GLfloat mtlPewterAmbient [4] =
{
    0.105882f, 0.058824f, 0.113725f, 1.000000f
};

const GLfloat mtlPewterDiffuse [4] =
{
    0.427451f, 0.470588f, 0.541176f, 1.000000f
};

const GLfloat mtlPewterSpecular [4] =
{
    0.333333f, 0.333333f, 0.521569f, 1.000000f
};

const GLfloat mtlPewterShininess = 9.84615f;

//////////////////////////////////////////////////////////////////////
// srebro
//////////////////////////////////////////////////////////////////////

const GLfloat mtlSilverAmbient [4] =
{
    0.192250f, 0.192250f, 0.192250f, 1.000000f
};

const GLfloat mtlSilverDiffuse [4] =
{
    0.507540f, 0.507540f, 0.507540f, 1.000000f
};

const GLfloat mtlSilverSpecular [4] =
{
    0.508273f, 0.508273f, 0.508273f, 1.000000f
};

const GLfloat mtlSilverShininess = 51.2f;

//////////////////////////////////////////////////////////////////////
// polerowane srebro
//////////////////////////////////////////////////////////////////////

const GLfloat mtlPolishedSilverAmbient [4] =
{
    0.231250f, 0.231250f, 0.231250f, 1.000000f
};

const GLfloat mtlPolishedSilverDiffuse [4] =
{
    0.277500f, 0.277500f, 0.277500f, 1.000000f
};

const GLfloat mtlPolishedSilverSpecular [4] =
{
    0.773911f, 0.773911f, 0.773911f, 1.000000f
};

const GLfloat mtlPolishedSilverShininess = 89.6f;

//////////////////////////////////////////////////////////////////////
// szmaragd
//////////////////////////////////////////////////////////////////////

const GLfloat mtlEmeraldAmbient [4] =
{
    0.021500f, 0.174500f, 0.021500f, 0.550000f
};

const GLfloat mtlEmeraldDiffuse [4] =
{
    0.075680f, 0.614240f, 0.075680f, 0.550000f
};

const GLfloat mtlEmeraldSpecular [4] =
{
    0.633000f, 0.727811f, 0.633000f, 0.550000f
};

const GLfloat mtlEmeraldShininess = 76.8f;

//////////////////////////////////////////////////////////////////////
// jadeit
//////////////////////////////////////////////////////////////////////

const GLfloat mtlJadeAmbient [4] =
{
    0.135000f, 0.222500f, 0.157500f, 0.950000f
};

const GLfloat mtlJadeDiffuse [4] =
{
    0.540000f, 0.890000f, 0.630000f, 0.950000f
};

const GLfloat mtlJadeSpecular [4] =
{
    0.316228f, 0.316228f, 0.316228f, 0.950000f
};

const GLfloat mtlJadeShininess = 12.8f;

//////////////////////////////////////////////////////////////////////
// obsydian (szk³o wulkaniczne)
//////////////////////////////////////////////////////////////////////

const GLfloat mtlObsidianAmbient [4] =
{
    0.053750f, 0.050000f, 0.066250f, 0.820000f
};

const GLfloat mtlObsidianDiffuse [4] =
{
    0.182750f, 0.170000f, 0.225250f, 0.820000f
};

const GLfloat mtlObsidianSpecular [4] =
{
    0.332741f, 0.328634f, 0.346435f, 0.820000f
};

const GLfloat mtlObsidianShininess = 38.4f;

//////////////////////////////////////////////////////////////////////
// per³a
//////////////////////////////////////////////////////////////////////

const GLfloat mtlPearlAmbient [4] =
{
    0.250000f, 0.207250f, 0.207250f, 0.922000f
};

const GLfloat mtlPearlDiffuse [4] =
{
    1.000000f, 0.829000f, 0.829000f, 0.922000f
};

const GLfloat mtlPearlSpecular [4] =
{
    0.296648f, 0.296648f, 0.296648f, 0.922000f
};

const GLfloat mtlPearlShininess = 11.264f;

//////////////////////////////////////////////////////////////////////
// rubin
//////////////////////////////////////////////////////////////////////

const GLfloat mtlRubyAmbient [4] =
{
    0.174500f, 0.011750f, 0.011750f, 0.550000f
};

const GLfloat mtlRubyDiffuse [4] =
{
    0.614240f, 0.041360f, 0.041360f, 0.550000f
};

const GLfloat mtlRubySpecular [4] =
{
    0.727811f, 0.626959f, 0.626959f, 0.550000f
};

const GLfloat mtlRubyShininess = 76.8f;

//////////////////////////////////////////////////////////////////////
// turkus
//////////////////////////////////////////////////////////////////////

const GLfloat mtlTurquoiseAmbient [4] =
{
    0.100000f, 0.187250f, 0.174500f, 0.800000f
};

const GLfloat mtlTurquoiseDiffuse [4] =
{
    0.396000f, 0.741510f, 0.691020f, 0.800000f
};

const GLfloat mtlTurquoiseSpecular [4] =
{
    0.297254f, 0.308290f, 0.306678f, 0.800000f
};

const GLfloat mtlTurquoiseShininess = 12.8f;

//////////////////////////////////////////////////////////////////////
// jasny bia³y
//////////////////////////////////////////////////////////////////////

const GLfloat mtlBrightWhiteAmbient [4] =
{
    0.2f, 0.2f, 0.2f, 1.000000f
};

const GLfloat mtlBrightWhiteDiffuse [4] =
{
    1.0f, 1.0f, 1.0f, 1.000000f
};

const GLfloat mtlBrightWhiteSpecular [4] =
{
    0.8f, 0.8f, 0.8f, 1.000000f
};

const GLfloat mtlBrightWhiteShininess = 51.2f;

//////////////////////////////////////////////////////////////////////
// mniej jasny bia³y
//////////////////////////////////////////////////////////////////////

const GLfloat mtlLessBrightWhiteAmbient [4] =
{
    0.2f, 0.2f, 0.2f, 1.000000f
};

const GLfloat mtlLessBrightWhiteDiffuse [4] =
{
    0.8f, 0.8f, 0.8f, 1.000000f
};

const GLfloat mtlLessBrightWhiteSpecular [4] =
{
    0.5f, 0.5f, 0.5f, 1.000000f
};

const GLfloat mtlLessBrightWhiteShininess = 44.8f;

//////////////////////////////////////////////////////////////////////
// ciep³y bia³y
//////////////////////////////////////////////////////////////////////

const GLfloat mtlWarmishWhiteAmbient [4] =
{
    0.3f, 0.2f, 0.2f, 1.000000f
};

const GLfloat mtlWarmishWhiteDiffuse [4] =
{
    1.0f, 0.9f, 0.8f, 1.000000f
};

const GLfloat mtlWarmishWhiteSpecular [4] =
{
    0.4f, 0.2f, 0.2f, 1.000000f
};

const GLfloat mtlWarmishWhiteShininess = 44.8f;

//////////////////////////////////////////////////////////////////////
// zimny bia³y
//////////////////////////////////////////////////////////////////////

const GLfloat mtlCoolishWhiteAmbient [4] =
{
    0.2f, 0.2f, 0.3f, 1.000000f
};

const GLfloat mtlCoolishWhiteDiffuse [4] =
{
    0.8f, 0.9f, 1.0f, 1.000000f
};

const GLfloat mtlCoolishWhiteSpecular [4] =
{
    0.2f, 0.2f, 0.4f, 1.000000f
};

const GLfloat mtlCoolishWhiteShininess = 44.8f;

//////////////////////////////////////////////////////////////////////
// czarny plastik
//////////////////////////////////////////////////////////////////////

const GLfloat mtlBlackPlasticAmbient [4] =
{
    0.000000f, 0.000000f, 0.000000f, 1.000000f
};

const GLfloat mtlBlackPlasticDiffuse [4] =
{
    0.010000f, 0.010000f, 0.010000f, 1.000000f
};

const GLfloat mtlBlackPlasticSpecular [4] =
{
    0.500000f, 0.500000f, 0.500000f, 1.000000f
};

const GLfloat mtlBlackPlasticShininess = 32.0f;

//////////////////////////////////////////////////////////////////////
// niebieskozielony plastik
//////////////////////////////////////////////////////////////////////

const GLfloat mtlCyanPlasticAmbient [4] =
{
    0.0f, 0.1f, 0.06f, 1.000000f
};

const GLfloat mtlCyanPlasticDiffuse [4] =
{
    0.0f, 0.50980392f, 0.50980392f, 1.000000f
};

const GLfloat mtlCyanPlasticSpecular [4] =
{
    0.50196078f, 0.50196078f, 0.50196078f, 1.000000f
};

const GLfloat mtlCyanPlasticShininess = 32.0f;

//////////////////////////////////////////////////////////////////////
// zielony plastik
//////////////////////////////////////////////////////////////////////

const GLfloat mtlGreenPlasticAmbient [4] =
{
    0.0f, 0.0f, 0.0f, 1.000000f
};

const GLfloat mtlGreenPlasticDiffuse [4] =
{
    0.1f, 0.35f, 0.1f, 1.000000f
};

const GLfloat mtlGreenPlasticSpecular [4] =
{
    0.45f, 0.55f, 0.45f, 1.000000f
};

const GLfloat mtlGreenPlasticShininess = 32.0f;

//////////////////////////////////////////////////////////////////////
// czerwony plastik
//////////////////////////////////////////////////////////////////////

const GLfloat mtlRedPlasticAmbient [4] =
{
    0.0f, 0.0f, 0.0f, 1.000000f
};

const GLfloat mtlRedPlasticDiffuse [4] =
{
    0.5f, 0.0f, 0.0f, 1.000000f
};

const GLfloat mtlRedPlasticSpecular [4] =
{
    0.7f, 0.6f, 0.6f, 1.000000f
};

const GLfloat mtlRedPlasticShininess = 32.0f;

//////////////////////////////////////////////////////////////////////
// bia³y plastik
//////////////////////////////////////////////////////////////////////

const GLfloat mtlWhitePlasticAmbient [4] =
{
    0.0f, 0.0f, 0.0f, 1.000000f
};

const GLfloat mtlWhitePlasticDiffuse [4] =
{
    0.55f, 0.55f, 0.55f, 1.000000f
};

const GLfloat mtlWhitePlasticSpecular [4] =
{
    0.70f, 0.70f, 0.70f, 1.000000f
};

const GLfloat mtlWhitePlasticShininess = 32.0f;

//////////////////////////////////////////////////////////////////////
// ¿ó³ty plastik
//////////////////////////////////////////////////////////////////////

const GLfloat mtlYellowPlasticAmbient [4] =
{
    0.0f, 0.0f, 0.0f,  1.000000f
};

const GLfloat mtlYellowPlasticDiffuse [4] =
{
    0.5f, 0.5f, 0.0f, 1.000000f
};

const GLfloat mtlYellowPlasticSpecular [4] =
{
    0.60f, 0.60f, 0.50f, 1.000000f
};

const GLfloat mtlYellowPlasticShininess = 32.0f;

//////////////////////////////////////////////////////////////////////
// czarna guma
//////////////////////////////////////////////////////////////////////

const GLfloat mtlBlackRubberAmbient [4] =
{
    0.020000f, 0.020000f, 0.020000f, 1.000000f
};

const GLfloat mtlBlackRubberDiffuse [4] =
{
    0.010000f, 0.010000f, 0.010000f, 1.000000f
};

const GLfloat mtlBlackRubberSpecular [4] =
{
    0.040000f, 0.040000f, 0.040000f, 1.000000f
};

const GLfloat mtlBlackRubberShininess = 10.0f;

//////////////////////////////////////////////////////////////////////
// niebieskozielona guma
//////////////////////////////////////////////////////////////////////

const GLfloat mtlCyanRubberAmbient [4] =
{
    0.0f, 0.05f, 0.05f, 1.000000f
};

const GLfloat mtlCyanRubberDiffuse [4] =
{
    0.4f, 0.5f, 0.5f, 1.000000f
};

const GLfloat mtlCyanRubberSpecular [4] =
{
    0.04f, 0.7f, 0.7f, 1.000000f
};

const GLfloat mtlCyanRubberShininess = 10.0f;

//////////////////////////////////////////////////////////////////////
// zielona guma
//////////////////////////////////////////////////////////////////////

const GLfloat mtlGreenRubberAmbient [4] =
{
    0.0f, 0.05f, 0.0f, 1.000000f
};

const GLfloat mtlGreenRubberDiffuse [4] =
{
    0.4f, 0.5f, 0.4f, 1.000000f
};

const GLfloat mtlGreenRubberSpecular [4] =
{
    0.04f, 0.7f, 0.04f, 1.000000f
};

const GLfloat mtlGreenRubberShininess = 10.0f;

//////////////////////////////////////////////////////////////////////
// czerwona guma
//////////////////////////////////////////////////////////////////////

const GLfloat mtlRedRubberAmbient [4] =
{
    0.05f, 0.0f, 0.0f, 1.000000f
};

const GLfloat mtlRedRubberDiffuse [4] =
{
    0.5f, 0.4f, 0.4f, 1.000000f
};

const GLfloat mtlRedRubberSpecular [4] =
{
    0.7f, 0.04f, 0.04f, 1.000000f
};

const GLfloat mtlRedRubberShininess = 10.0f;

//////////////////////////////////////////////////////////////////////
// bia³a guma
//////////////////////////////////////////////////////////////////////

const GLfloat mtlWhiteRubberAmbient [4] =
{
    0.05f, 0.05f, 0.05f, 1.000000f
};

const GLfloat mtlWhiteRubberDiffuse [4] =
{
    0.5f, 0.5f, 0.5f, 1.000000f
};

const GLfloat mtlWhiteRubberSpecular [4] =
{
    0.7f, 0.7f, 0.7f, 1.000000f
};

const GLfloat mtlWhiteRubberShininess = 10.0f;

//////////////////////////////////////////////////////////////////////
// ¿ó³ta guma
//////////////////////////////////////////////////////////////////////

const GLfloat mtlYellowRubberAmbient [4] =
{
    0.05f, 0.05f, 0.0f, 1.000000f
};

const GLfloat mtlYellowRubberDiffuse [4] =
{
    0.5f, 0.5f, 0.4f, 1.000000f
};

const GLfloat mtlYellowRubberSpecular [4] =
{
    0.7f, 0.7f, 0.04f, 1.000000f
};

const GLfloat mtlYellowRubberShininess = 10.0f;

//////////////////////////////////////////////////////////////////////
// sta³e okreœlaj¹ce poszczególne materia³y
//////////////////////////////////////////////////////////////////////
enum
{
    MTL_DEFAULT,            // materia³ domyœlny
    MTL_BRASS,              // mosi¹dz
    MTL_BRONZE,             // br¹z
    MTL_POLISHED_BRONZE,    // polerowany br¹z
    MTL_CHROME,             // chrom
    MTL_COPPER,             // miedŸ
    MTL_POLISHED_COPPER,    // polerowana miedŸ
    MTL_GOLD,               // z³oto
    MTL_POLISHED_GOLD,      // polerowane z³oto
    MTL_PEWTER,             // grafit (cyna z o³owiem)
    MTL_SILVER,             // srebro
    MTL_POLISHED_SILVER,    // polerowane srebro
    MTL_EMERALD,            // szmaragd
    MTL_JADE,               // jadeit
    MTL_OBSIDIAN,           // obsydian
    MTL_PEARL,              // per³a
    MTL_RUBY,               // rubin
    MTL_TURQUOISE,          // turkus
    MTL_BRIGHT_WHITE,       // jasny bia³y
    MTL_LESS_BRIGHT_WHITE,  // mniej jasny bia³y
    MTL_WARMISH_WHITE,      // ciep³y bia³y
    MTL_COOLISH_WHITE,      // zimny bia³y
    MTL_BLACK_PLASTIC,      // czarny plastik
    MTL_CYAN_PLASTIC,       // niebieskozielony plastik
    MTL_GREEN_PLASTIC,      // zielony plastik
    MTL_RED_PLASTIC,        // czerwony plastik
    MTL_WHITE_PLASTIC,      // bia³y plastik
    MTL_YELLOW_PLASTIC,     // ¿ó³ty plastik
    MTL_BLACK_RUBBER,       // czarna guma
    MTL_CYAN_RUBBER,        // niebieskozielona guma
    MTL_GREEN_RUBBER,       // zielona guma
    MTL_RED_RUBBER,         // czerwona guma
    MTL_WHITE_RUBBER,       // bia³a guma
    MTL_YELLOW_RUBBER       // ¿ó³ta guma
};

//////////////////////////////////////////////////////////////////////
// sta³e okreœlaj¹ce poszczególne w³aœciwoœci materia³u
//////////////////////////////////////////////////////////////////////
enum
{
    MTL_AMBIENT,
    MTL_DIFFUSE,
    MTL_SPECULAR,
    MTL_SHININESS
};

//////////////////////////////////////////////////////////////////////
// pobranie wybranej w³aœciwoœci okreœlonego materia³u
//////////////////////////////////////////////////////////////////////
inline const GLfloat *GetMaterial( const int material, const int properties )
{
    switch( material )
    {
        // materia³ domyœlny
        case MTL_DEFAULT:
            if( properties == MTL_AMBIENT ) return mtlBrightWhiteAmbient;       // { 0.2, 0.2, 0.2, 1.0 }
            if( properties == MTL_DIFFUSE ) return mtlBrightWhiteSpecular;      // { 0.8, 0.8, 0.8, 1.0 }
            if( properties == MTL_SPECULAR ) return mtlBlackPlasticAmbient;     // { 0.0, 0.0, 0.0, 1.0 }
            if( properties == MTL_SHININESS ) return mtlBlackPlasticAmbient;    // 0.0
            break;

        // materia³ - mosi¹dz
        case MTL_BRASS:
            if( properties == MTL_AMBIENT ) return mtlBrassAmbient;
            if( properties == MTL_DIFFUSE ) return mtlBrassDiffuse;
            if( properties == MTL_SPECULAR ) return mtlBrassSpecular;
            if( properties == MTL_SHININESS ) return &mtlBrassShininess;
            break;

        // materia³ - br¹z
        case MTL_BRONZE:
            if( properties == MTL_AMBIENT ) return mtlBronzeAmbient;
            if( properties == MTL_DIFFUSE ) return mtlBronzeDiffuse;
            if( properties == MTL_SPECULAR ) return mtlBronzeSpecular;
            if( properties == MTL_SHININESS ) return &mtlBronzeShininess;
            break;

        // materia³ - polerowany br¹z
        case MTL_POLISHED_BRONZE:
            if( properties == MTL_AMBIENT ) return mtlPolishedBronzeAmbient;
            if( properties == MTL_DIFFUSE ) return mtlPolishedBronzeDiffuse;
            if( properties == MTL_SPECULAR ) return mtlPolishedBronzeSpecular;
            if( properties == MTL_SHININESS ) return &mtlPolishedBronzeShininess;
            break;

        // materia³ - chrom
        case MTL_CHROME:
            if( properties == MTL_AMBIENT ) return mtlChromeAmbient;
            if( properties == MTL_DIFFUSE ) return mtlChromeDiffuse;
            if( properties == MTL_SPECULAR ) return mtlChromeSpecular;
            if( properties == MTL_SHININESS ) return &mtlChromeShininess;
            break;

        // materia³ - miedŸ
        case MTL_COPPER:
            if( properties == MTL_AMBIENT ) return mtlCopperAmbient;
            if( properties == MTL_DIFFUSE ) return mtlCopperDiffuse;
            if( properties == MTL_SPECULAR ) return mtlCopperSpecular;
            if( properties == MTL_SHININESS ) return &mtlCopperShininess;
            break;

        // materia³ - polerowana miedŸ
        case MTL_POLISHED_COPPER:
            if( properties == MTL_AMBIENT ) return mtlPolishedCopperAmbient;
            if( properties == MTL_DIFFUSE ) return mtlPolishedCopperDiffuse;
            if( properties == MTL_SPECULAR ) return mtlPolishedCopperSpecular;
            if( properties == MTL_SHININESS ) return &mtlPolishedCopperShininess;
            break;

        // materia³ - z³oto
        case MTL_GOLD:
            if( properties == MTL_AMBIENT ) return mtlGoldAmbient;
            if( properties == MTL_DIFFUSE ) return mtlGoldDiffuse;
            if( properties == MTL_SPECULAR ) return mtlGoldSpecular;
            if( properties == MTL_SHININESS ) return &mtlGoldShininess;
            break;

        // materia³ - polerowane z³oto
        case MTL_POLISHED_GOLD:
            if( properties == MTL_AMBIENT ) return mtlPolishedGoldAmbient;
            if( properties == MTL_DIFFUSE ) return mtlPolishedGoldDiffuse;
            if( properties == MTL_SPECULAR ) return mtlPolishedGoldSpecular;
            if( properties == MTL_SHININESS ) return &mtlPolishedGoldShininess;
            break;

        // materia³ - grafit (cyna z o³owiem)
        case MTL_PEWTER:
            if( properties == MTL_AMBIENT ) return mtlPewterAmbient;
            if( properties == MTL_DIFFUSE ) return mtlPewterDiffuse;
            if( properties == MTL_SPECULAR ) return mtlPewterSpecular;
            if( properties == MTL_SHININESS ) return &mtlPewterShininess;
            break;

        // materia³ - srebro
        case MTL_SILVER:
            if( properties == MTL_AMBIENT ) return mtlSilverAmbient;
            if( properties == MTL_DIFFUSE ) return mtlSilverDiffuse;
            if( properties == MTL_SPECULAR ) return mtlSilverSpecular;
            if( properties == MTL_SHININESS ) return &mtlSilverShininess;
            break;

        // materia³ - polerowane srebro
        case MTL_POLISHED_SILVER:
            if( properties == MTL_AMBIENT ) return mtlPolishedSilverAmbient;
            if( properties == MTL_DIFFUSE ) return mtlPolishedSilverDiffuse;
            if( properties == MTL_SPECULAR ) return mtlPolishedSilverSpecular;
            if( properties == MTL_SHININESS ) return &mtlPolishedSilverShininess;
            break;

        // materia³ - szmaragd
        case MTL_EMERALD:
            if( properties == MTL_AMBIENT ) return mtlEmeraldAmbient;
            if( properties == MTL_DIFFUSE ) return mtlEmeraldDiffuse;
            if( properties == MTL_SPECULAR ) return mtlEmeraldSpecular;
            if( properties == MTL_SHININESS ) return &mtlEmeraldShininess;
            break;

        // materia³ - jadeit
        case MTL_JADE:
            if( properties == MTL_AMBIENT ) return mtlJadeAmbient;
            if( properties == MTL_DIFFUSE ) return mtlJadeDiffuse;
            if( properties == MTL_SPECULAR ) return mtlJadeSpecular;
            if( properties == MTL_SHININESS ) return &mtlJadeShininess;
            break;

        // materia³ - obsydian
        case MTL_OBSIDIAN:
            if( properties == MTL_AMBIENT ) return mtlObsidianAmbient;
            if( properties == MTL_DIFFUSE ) return mtlObsidianDiffuse;
            if( properties == MTL_SPECULAR ) return mtlObsidianSpecular;
            if( properties == MTL_SHININESS ) return &mtlObsidianShininess;
            break;

        // materia³ - per³a
        case MTL_PEARL:
            if( properties == MTL_AMBIENT ) return mtlPearlAmbient;
            if( properties == MTL_DIFFUSE ) return mtlPearlDiffuse;
            if( properties == MTL_SPECULAR ) return mtlPearlSpecular;
            if( properties == MTL_SHININESS ) return &mtlPearlShininess;
            break;

        // metaria³ - rubin
        case MTL_RUBY:
            if( properties == MTL_AMBIENT ) return mtlRubyAmbient;
            if( properties == MTL_DIFFUSE ) return mtlRubyDiffuse;
            if( properties == MTL_SPECULAR ) return mtlRubySpecular;
            if( properties == MTL_SHININESS ) return &mtlRubyShininess;
            break;

        // materia³ - turkus
        case MTL_TURQUOISE:
            if( properties == MTL_AMBIENT ) return mtlTurquoiseAmbient;
            if( properties == MTL_DIFFUSE ) return mtlTurquoiseDiffuse;
            if( properties == MTL_SPECULAR ) return mtlTurquoiseSpecular;
            if( properties == MTL_SHININESS ) return &mtlTurquoiseShininess;
            break;

        // materia³ - jasny bia³y
        case MTL_BRIGHT_WHITE:
            if( properties == MTL_AMBIENT ) return mtlBrightWhiteAmbient;
            if( properties == MTL_DIFFUSE ) return mtlBrightWhiteDiffuse;
            if( properties == MTL_SPECULAR ) return mtlBrightWhiteSpecular;
            if( properties == MTL_SHININESS ) return &mtlBrightWhiteShininess;
            break;

        // materia³ -  mniej jasny bia³y
        case MTL_LESS_BRIGHT_WHITE:
            if( properties == MTL_AMBIENT ) return mtlLessBrightWhiteAmbient;
            if( properties == MTL_DIFFUSE ) return mtlLessBrightWhiteDiffuse;
            if( properties == MTL_SPECULAR ) return mtlLessBrightWhiteSpecular;
            if( properties == MTL_SHININESS ) return &mtlLessBrightWhiteShininess;
            break;

        // materia³ - ciep³y bia³y
        case MTL_WARMISH_WHITE:
            if( properties == MTL_AMBIENT ) return mtlWarmishWhiteAmbient;
            if( properties == MTL_DIFFUSE ) return mtlWarmishWhiteDiffuse;
            if( properties == MTL_SPECULAR ) return mtlWarmishWhiteSpecular;
            if( properties == MTL_SHININESS ) return &mtlWarmishWhiteShininess;
            break;

        // materia³ - zimny bia³y
        case MTL_COOLISH_WHITE:
            if( properties == MTL_AMBIENT ) return mtlCoolishWhiteAmbient;
            if( properties == MTL_DIFFUSE ) return mtlCoolishWhiteDiffuse;
            if( properties == MTL_SPECULAR ) return mtlCoolishWhiteSpecular;
            if( properties == MTL_SHININESS ) return &mtlCoolishWhiteShininess;
            break;

        // materia³ - czarny plastik
        case MTL_BLACK_PLASTIC:
            if( properties == MTL_AMBIENT ) return mtlBlackPlasticAmbient;
            if( properties == MTL_DIFFUSE ) return mtlBlackPlasticDiffuse;
            if( properties == MTL_SPECULAR ) return mtlBlackPlasticSpecular;
            if( properties == MTL_SHININESS ) return &mtlBlackPlasticShininess;
            break;

        // materia³ - niebieskozielony plastik
        case MTL_CYAN_PLASTIC:
            if( properties == MTL_AMBIENT ) return mtlCyanPlasticAmbient;
            if( properties == MTL_DIFFUSE ) return mtlCyanPlasticDiffuse;
            if( properties == MTL_SPECULAR ) return mtlCyanPlasticSpecular;
            if( properties == MTL_SHININESS ) return &mtlCyanPlasticShininess;
            break;

        // materia³ - zielony plastik
        case MTL_GREEN_PLASTIC:
            if( properties == MTL_AMBIENT ) return mtlGreenPlasticAmbient;
            if( properties == MTL_DIFFUSE ) return mtlGreenPlasticDiffuse;
            if( properties == MTL_SPECULAR ) return mtlGreenPlasticSpecular;
            if( properties == MTL_SHININESS ) return &mtlGreenPlasticShininess;
            break;

        // materia³ - czerwony plastik
        case MTL_RED_PLASTIC:
            if( properties == MTL_AMBIENT ) return mtlRedPlasticAmbient;
            if( properties == MTL_DIFFUSE ) return mtlRedPlasticDiffuse;
            if( properties == MTL_SPECULAR ) return mtlRedPlasticSpecular;
            if( properties == MTL_SHININESS ) return &mtlRedPlasticShininess;
            break;

        // materia³ - bia³y plastik
        case MTL_WHITE_PLASTIC:
            if( properties == MTL_AMBIENT ) return mtlWhitePlasticAmbient;
            if( properties == MTL_DIFFUSE ) return mtlWhitePlasticDiffuse;
            if( properties == MTL_SPECULAR ) return mtlWhitePlasticSpecular;
            if( properties == MTL_SHININESS ) return &mtlWhitePlasticShininess;
            break;

        // materia³ - ¿ó³ty plastik
        case MTL_YELLOW_PLASTIC:
            if( properties == MTL_AMBIENT ) return mtlYellowPlasticAmbient;
            if( properties == MTL_DIFFUSE ) return mtlYellowPlasticDiffuse;
            if( properties == MTL_SPECULAR ) return mtlYellowPlasticSpecular;
            if( properties == MTL_SHININESS ) return &mtlYellowPlasticShininess;
            break;

        // materia³ - czarna guma
        case MTL_BLACK_RUBBER:
            if( properties == MTL_AMBIENT ) return mtlBlackRubberAmbient;
            if( properties == MTL_DIFFUSE ) return mtlBlackRubberDiffuse;
            if( properties == MTL_SPECULAR ) return mtlBlackRubberSpecular;
            if( properties == MTL_SHININESS ) return &mtlBlackRubberShininess;
            break;

        // materia³ - niebieskozielona guma
        case MTL_CYAN_RUBBER:
            if( properties == MTL_AMBIENT ) return mtlCyanRubberAmbient;
            if( properties == MTL_DIFFUSE ) return mtlCyanRubberDiffuse;
            if( properties == MTL_SPECULAR ) return mtlCyanRubberSpecular;
            if( properties == MTL_SHININESS ) return &mtlCyanRubberShininess;
            break;

        // materia³ - zielona guma
        case MTL_GREEN_RUBBER:
            if( properties == MTL_AMBIENT ) return mtlGreenRubberAmbient;
            if( properties == MTL_DIFFUSE ) return mtlGreenRubberDiffuse;
            if( properties == MTL_SPECULAR ) return mtlGreenRubberSpecular;
            if( properties == MTL_SHININESS ) return &mtlGreenRubberShininess;
            break;

        // materia³ - czerwona guma
        case MTL_RED_RUBBER:
            if( properties == MTL_AMBIENT ) return mtlRedRubberAmbient;
            if( properties == MTL_DIFFUSE ) return mtlRedRubberDiffuse;
            if( properties == MTL_SPECULAR ) return mtlRedRubberSpecular;
            if( properties == MTL_SHININESS ) return &mtlRedRubberShininess;
            break;

        // materia³ - bia³a guma
        case MTL_WHITE_RUBBER:
            if( properties == MTL_AMBIENT ) return mtlWhiteRubberAmbient;
            if( properties == MTL_DIFFUSE ) return mtlWhiteRubberDiffuse;
            if( properties == MTL_SPECULAR ) return mtlWhiteRubberSpecular;
            if( properties == MTL_SHININESS ) return &mtlWhiteRubberShininess;
            break;

        // materia³ - ¿ó³ta guma
        case MTL_YELLOW_RUBBER:
            if( properties == MTL_AMBIENT ) return mtlYellowRubberAmbient;
            if( properties == MTL_DIFFUSE ) return mtlYellowRubberDiffuse;
            if( properties == MTL_SPECULAR ) return mtlYellowRubberSpecular;
            if( properties == MTL_SHININESS ) return &mtlYellowRubberShininess;
            break;
    }

    // b³êdne dane
    return NULL;
}

//////////////////////////////////////////////////////////////////////
// pobranie angielskiej nazwy okreœlonego materia³u
//////////////////////////////////////////////////////////////////////
inline const char *GetMaterialName( const int material )
{
    switch( material )
    {
        // materia³ domyœlny
        case MTL_DEFAULT:           return "default";

        // materia³ - mosi¹dz
        case MTL_BRASS:             return "Brass";

        // materia³ - br¹z
        case MTL_BRONZE:            return "Bronze";

        // materia³ - polerowany br¹z
        case MTL_POLISHED_BRONZE:   return "Polished Bronze";

        // materia³ - chrom
        case MTL_CHROME:            return "Chrome";

        // materia³ - miedŸ
        case MTL_COPPER:            return "Copper";

        // materia³ - polerowana miedŸ
        case MTL_POLISHED_COPPER:   return "Polished Copper";

        // materia³ - z³oto
        case MTL_GOLD:              return "Gold";

        // materia³ - polerowane z³oto
        case MTL_POLISHED_GOLD:     return "Polished Gold";

        // materia³ - grafit (cyna z o³owiem)
        case MTL_PEWTER:            return "Pewter";

        // materia³ - srebro
        case MTL_SILVER:            return "Silver";

        // materia³ - polerowane srebro
        case MTL_POLISHED_SILVER:   return "Polished Silver";

        // materia³ - szmaragd
        case MTL_EMERALD:           return "Emerald";

        // materia³ - jadeit
        case MTL_JADE:              return "Jade";

        // materia³ - obsydian
        case MTL_OBSIDIAN:          return "Obsidian";

        // materia³ - per³a
        case MTL_PEARL:             return "Pearl";

        // metaria³ - rubin
        case MTL_RUBY:              return "Ruby";

        // materia³ - turkus
        case MTL_TURQUOISE:         return "Turquoise";

        // materia³ - jasny bia³y
        case MTL_BRIGHT_WHITE:      return "Bright White";

        // materia³ -  mniej jasny bia³y
        case MTL_LESS_BRIGHT_WHITE: return "Less Bright White";

        // materia³ - ciep³y bia³y
        case MTL_WARMISH_WHITE:     return "Warmish White";

        // materia³ - zimny bia³y
        case MTL_COOLISH_WHITE:     return "Coolish White";

        // materia³ - czarny plastik
        case MTL_BLACK_PLASTIC:     return "Black Plastic";

        // materia³ - niebieskozielony plastik
        case MTL_CYAN_PLASTIC:      return "Cyan Plastic";

        // materia³ - zielony plastik
        case MTL_GREEN_PLASTIC:     return "Green Plastic";

        // materia³ - czerwony plastik
        case MTL_RED_PLASTIC:       return "Red Plastic";

        // materia³ - bia³y plastik
        case MTL_WHITE_PLASTIC:     return "White Plastic";

        // materia³ - ¿ó³ty plastik
        case MTL_YELLOW_PLASTIC:    return "Yellow Plastic";

        // materia³ - czarna guma
        case MTL_BLACK_RUBBER:      return "Black Rubber";

        // materia³ - niebieskozielona guma
        case MTL_CYAN_RUBBER:       return "Cyan Rubber";

        // materia³ - zielona guma
        case MTL_GREEN_RUBBER:      return "Green Rubber";

        // materia³ - czerwona guma
        case MTL_RED_RUBBER:        return "Red Rubber";

        // materia³ - bia³a guma
        case MTL_WHITE_RUBBER:      return "White Rubber";

        // materia³ - ¿ó³ta guma
        case MTL_YELLOW_RUBBER:     return "Yellow Rubber";
    }

    // b³êdne dane
    return "";
}

#endif // __MATERIALS__H__
