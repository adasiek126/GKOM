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
// struktura opisuj�ca parametry �r�d�a �wiat�a
//////////////////////////////////////////////////////////////////////
struct LightSourceParameters
{
    vec4 ambient;               // intensywno�� �wiat�a otoczenia; oznaczenie La
    vec4 diffuse;               // intensywno�� �wiat�a rozproszonego; oznaczenie Ld
    vec4 specular;              // intensywno�� �wiat�a zwierciadlanego; oznaczenie Ls
    vec4 position;              // po�o�enie �r�d�a �wiat�a punktowego (position.w = 1.0)
                                // lub wektor kierunku �wiat�a kierunkowego, skierowany
                                // do �r�d�a �wiat�a (position.w = 0.0)
    float constantAttenuation;  // sta�y wsp�czynnik t�umienia �wiat�a; oznaczenie kc
    float linearAttenuation;    // liniowy wsp�czynnik t�umienia �wiat�a; oznaczenie kl
    float quadraticAttenuation; // kwadratowy wsp�czynnik t�umienia �wiat�a; oznaczenie kq
};

//////////////////////////////////////////////////////////////////////
// maksymalna liczba �r�de� �wiat�a
//////////////////////////////////////////////////////////////////////
const int maxLights = 4;

//////////////////////////////////////////////////////////////////////
// tablica z parametrami poszczeg�lnych �r�de� �wiat�a
//////////////////////////////////////////////////////////////////////
uniform LightSourceParameters lightSource[maxLights] =  LightSourceParameters[maxLights]
(
    // parametry �r�d�a �wiat�a nr 0
    LightSourceParameters( vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 1.0, 1.0, 1.0, 1.0 ),
                           vec4( 1.0, 1.0, 1.0, 1.0 ),
                           vec4( 0.0, 0.0, 1.0, 0.0 ),
                           1.0,
                           0.0,
                           0.0 ),
    // parametry �r�d�a �wiat�a nr 1
    LightSourceParameters( vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 1.0, 0.0 ),
                           1.0,
                           0.0,
                           0.0 ),
    // parametry �r�d�a �wiat�a nr 2
    LightSourceParameters( vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 1.0, 0.0 ),
                           1.0,
                           0.0,
                           0.0 ),
    // parametry �r�d�a �wiat�a nr 3
    LightSourceParameters( vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 0.0, 1.0 ),
                           vec4( 0.0, 0.0, 1.0, 0.0 ),
                           1.0,
                           0.0,
                           0.0 )
);

//////////////////////////////////////////////////////////////////////
// pobranie parametr�w wybranego �r�d�a �wiat�a
//////////////////////////////////////////////////////////////////////
LightSourceParameters LightSource( const int light )
{
    return lightSource[light];
}

//////////////////////////////////////////////////////////////////////
// struktura opisuj�ca parametry modelu o�wietlenia
//////////////////////////////////////////////////////////////////////
struct LightModelParameters
{
    vec4 ambient;   // globalne �wiat�o otoczenia; oznaczenie Ga
};

//////////////////////////////////////////////////////////////////////
// parametry modelu o�wietlenia
//////////////////////////////////////////////////////////////////////
uniform LightModelParameters lightModel = LightModelParameters
(
    vec4( 0.2, 0.2, 0.2, 1.0 )
);

//////////////////////////////////////////////////////////////////////
// wsp�rz�dne po�o�enia obserwatora
//////////////////////////////////////////////////////////////////////
uniform vec4 eyePosition = vec4( 0.0, 0.0, 0.0, 1.0 );

//////////////////////////////////////////////////////////////////////
// pobranie po�o�enia obserwatora
//////////////////////////////////////////////////////////////////////
vec4 EyePosition()
{
    return eyePosition;
}

//////////////////////////////////////////////////////////////////////
// globalne �wiat�o otoczenia
// ambient - wsp�czynnik odbicia �wiat�a otoczenia; oznaczenie Ma
//////////////////////////////////////////////////////////////////////
vec4 GlobalAmbientLight( const vec4 ambient )
{
    return lightModel.ambient * ambient;
}

//////////////////////////////////////////////////////////////////////
// lokalne �wiat�o otoczenia
// light - numer �r�d�a �wiat�a
// ambient - wsp�czynnik odbicia �wiat�a otoczenia; oznaczenie Ma
//////////////////////////////////////////////////////////////////////
vec4 LocalAmbientLight( const int light, const vec4 ambient )
{
    return lightSource[light].ambient * ambient;
}
