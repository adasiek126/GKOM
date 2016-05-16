//////////////////////////////////////////////////////////////////////
// (c) Janusz Ganczarski
// http://www.januszg.hg.pl
// JanuszG@enter.net.pl
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// GLSL 1.50
//////////////////////////////////////////////////////////////////////
#version 150

//////////////////////////////////////////////////////////////////////
// struktura opisuj¹ca parametry Ÿród³a œwiat³a
//////////////////////////////////////////////////////////////////////
struct LightSourceParameters
{
    vec4 ambient;               // intensywnoœæ œwiat³a otoczenia; oznaczenie La
    vec4 diffuse;               // intensywnoœæ œwiat³a rozproszonego; oznaczenie Ld
    vec4 specular;              // intensywnoœæ œwiat³a zwierciadlanego; oznaczenie Ls
    vec4 position;              // po³o¿enie Ÿród³a œwiat³a punktowego (position.w = 1.0)
                                // lub wektor kierunku œwiat³a kierunkowego, skierowany
                                // do Ÿród³a œwiat³a (position.w = 0.0)
    float constantAttenuation;  // sta³y wspó³czynnik t³umienia œwiat³a; oznaczenie kc
    float linearAttenuation;    // liniowy wspó³czynnik t³umienia œwiat³a; oznaczenie kl
    float quadraticAttenuation; // kwadratowy wspó³czynnik t³umienia œwiat³a; oznaczenie kq
};

//////////////////////////////////////////////////////////////////////
// maksymalna liczba Ÿróde³ œwiat³a
//////////////////////////////////////////////////////////////////////
const int maxLights = 4;

//////////////////////////////////////////////////////////////////////
// tablica z parametrami poszczególnych Ÿróde³ œwiat³a
//////////////////////////////////////////////////////////////////////
uniform LightSourceParameters lightSource[maxLights] =  LightSourceParameters[maxLights]
(
    // parametry Ÿród³a œwiat³a nr 0
    LightSourceParameters( vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 1.0, 1.0, 1.0, 1.0 ),
                           vec4( 1.0, 1.0, 1.0, 1.0 ),
                           vec4( 0.0, 0.0, 1.0, 0.0 ),
                           1.0,
                           0.0,
                           0.0 ),
    // parametry Ÿród³a œwiat³a nr 1
    LightSourceParameters( vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 1.0, 0.0 ),
                           1.0,
                           0.0,
                           0.0 ),
    // parametry Ÿród³a œwiat³a nr 2
    LightSourceParameters( vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 1.0, 0.0 ),
                           1.0,
                           0.0,
                           0.0 ),
    // parametry Ÿród³a œwiat³a nr 3
    LightSourceParameters( vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 1.0, 0.0 ),
                           1.0,
                           0.0,
                           0.0 )
);

//////////////////////////////////////////////////////////////////////
// pobranie parametrów wybranego Ÿród³a œwiat³a
//////////////////////////////////////////////////////////////////////
LightSourceParameters LightSource( const int light )
{
    return lightSource[light];
}

//////////////////////////////////////////////////////////////////////
// struktura opisuj¹ca parametry modelu oœwietlenia
//////////////////////////////////////////////////////////////////////
struct LightModelParameters
{
    vec4 ambient;   // globalne œwiat³o otoczenia; oznaczenie Ga
};

//////////////////////////////////////////////////////////////////////
// parametry modelu oœwietlenia
//////////////////////////////////////////////////////////////////////
uniform LightModelParameters lightModel = LightModelParameters
(
    vec4( 0.2, 0.2, 0.2, 1.0 )
);

//////////////////////////////////////////////////////////////////////
// wspó³rzêdne po³o¿enia obserwatora
//////////////////////////////////////////////////////////////////////
uniform vec4 eyePosition = vec4( 0.0, 0.0, 0.0, 1.0 );

//////////////////////////////////////////////////////////////////////
// pobranie po³o¿enia obserwatora
//////////////////////////////////////////////////////////////////////
vec4 EyePosition()
{
    return eyePosition;
}

//////////////////////////////////////////////////////////////////////
// globalne œwiat³o otoczenia
// ambient - wspó³czynnik odbicia œwiat³a otoczenia; oznaczenie Ma
//////////////////////////////////////////////////////////////////////
vec4 GlobalAmbientLight( const vec4 ambient )
{
    return lightModel.ambient * ambient;
}

//////////////////////////////////////////////////////////////////////
// lokalne œwiat³o otoczenia
// light - numer Ÿród³a œwiat³a
// ambient - wspó³czynnik odbicia œwiat³a otoczenia; oznaczenie Ma
//////////////////////////////////////////////////////////////////////
vec4 LocalAmbientLight( const int light, const vec4 ambient )
{
    return lightSource[light].ambient * ambient;
}
