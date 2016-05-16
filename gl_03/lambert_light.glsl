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
// prototypy funkcji
//////////////////////////////////////////////////////////////////////
LightSourceParameters LightSource( const int light );
vec4 GlobalAmbientLight( const vec4 ambient );
vec4 LocalAmbientLight( const int light, const vec4 ambient );

//////////////////////////////////////////////////////////////////////
// �wiat�o kierunkowe w modelu Lamberta
// light - numer �r�d�a �wiat�a
// normal - znormalizowany wektor normalny
// position - wsp�rz�dne wierzcho�ka
// wektor kierunku �wiat�a lightSource[light].position.xyz musi by�
// znormalizowany i wyra�ony w tym samym uk�adzie wsp�rz�dnych co wektor
// normalny i wsp�rz�dne wierzcho�ka; ponadto wektor ten
// musi by� zorientowany w kierunku do �r�d�a �wiat�a
// diffuse - wsp�czynnik odbicia �wiat�a rozproszonego; oznaczenie Md
//////////////////////////////////////////////////////////////////////
vec4 LambertDirectionalLight( const int light, const vec3 normal,
                              const vec3 position, const vec4 diffuse )
{
    // pobranie parametr�w danego �r�d�a �wiat�a
    LightSourceParameters lightSource = LightSource( light );

    // obliczanie cosinusa k�ta odbicia �wiat�a
    float NdotL = dot( normal, lightSource.position.xyz );

    // obliczanie �wiat�a odbitego tylko dla powierzchni widocznej;
    // warto�� 0.0 k�ta odbicia oznacza, �e k�t odbicia jest w przedziale <0;90)
    if( NdotL > 0.0 )
        // ko�cowe obliczenie sk�adowych o�wietlenia
        return NdotL * diffuse * lightSource.diffuse;
    else
        // dla NdotL = 0.0 powierzchnia nie jest widoczna
        return vec4( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// �wiat�o punktowe w modelu Lamberta
// light - numer �r�d�a �wiat�a
// normal - znormalizowany wektor normalny
// position - wsp�rz�dne wierzcho�ka
// po�o�enie �r�d�a �wiat�a lightSource[light].position.xyz musi by�
// wyra�one w tym samym uk�adzie wsp�rz�dnych co wektor normalny
// i wsp�rz�dne wierzcho�ka
// ambient - wsp�czynnik odbicia �wiat�a otoczenia; oznaczenie Ma
// diffuse - wsp�czynnik odbicia �wiat�a rozproszonego; oznaczenie Md
//////////////////////////////////////////////////////////////////////
vec4 LambertPointLight( const int light, const vec3 normal, const vec3 position,
                        const vec4 ambient, const vec4 diffuse )
{
    // pobranie parametr�w danego �r�d�a �wiat�a
    LightSourceParameters lightSource = LightSource( light );

    // wektor z bie��cego wierzcho�ka do �r�d�a �wiat�a - wektor kierunku �r�d�a �wiat�a
    vec3 lightVec = lightSource.position.xyz - position;

    // obliczenie odleg�o�ci od bie��cego wierzcho�ka do �r�d�a �wiat�a
    float distance = length( lightVec );

    // normalizacja wektora kierunku �r�d�a �wiat�a
    lightVec = normalize( lightVec );

    // obliczanie cosinusa k�ta odbicia �wiat�a
    float NdotL = dot( normal, lightVec );

    // obliczanie �wiat�a odbitego tylko dla powierzchni widocznej;
    // warto�� 0.0 k�ta odbicia oznacza, �e k�t odbicia jest w przedziale <0;90)
    if( NdotL > 0.0 )
    {
        // obliczenie wsp�czynnika t�umienia �wiat�a
        float att = 1.0 / ( lightSource.constantAttenuation +
                            lightSource.linearAttenuation * distance +
                            lightSource.quadraticAttenuation * distance * distance );

        // ko�cowe obliczenie sk�adowych o�wietlenia
        return att * ( LocalAmbientLight( light, ambient ) + NdotL * diffuse * lightSource.diffuse );
    }
    else
        // dla NdotL = 0.0 powierzchnia nie jest widoczna
        return vec4( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// o�wietlenie Lamberta
// wymogi dotycz�ce parametr�w jak w opisach funkcji:
// LambertDirectionalLight i LambertPointLight
//////////////////////////////////////////////////////////////////////
vec4 LambertLight( const int light, const vec3 normal, const vec3 position,
                    const vec4 ambient, const vec4 diffuse )
{
    // �wiat�o kierunkowe
    if( LightSource( light ).position.w == 0.0 )
        return LambertDirectionalLight( light, normal, position, diffuse ) +
                LocalAmbientLight( light, ambient ) + GlobalAmbientLight( ambient );
    else
    // �wiat�o punktowe
        return LambertPointLight( light, normal, position, ambient, diffuse ) +
                GlobalAmbientLight( ambient );
}

//////////////////////////////////////////////////////////////////////
// �wiat�o kierunkowe w modelu Lamberta z przemieszczeniem
// wektora/kierunku �wiat�a
// light - numer �r�d�a �wiat�a
// normal - znormalizowany wektor normalny
// position - wsp�rz�dne wierzcho�ka
// wektor kierunku �wiat�a lightSource[light].position.xyz musi by�
// znormalizowany i wyra�ony w tym samym uk�adzie wsp�rz�dnych co wektor
// normalny i wsp�rz�dne wierzcho�ka; ponadto wektor ten
// musi by� zorientowany w kierunku do �r�d�a �wiat�a
// diffuse - wsp�czynnik odbicia �wiat�a rozproszonego; oznaczenie Md
// TBN - macierz przekszta�cenia wektora/kierunku �wiat�a
//////////////////////////////////////////////////////////////////////
vec4 LambertDirectionalLight( const int light, const vec3 normal,
                              const vec3 position, const vec4 diffuse,
                              const mat3 TBN )
{
    // pobranie parametr�w danego �r�d�a �wiat�a
    LightSourceParameters lightSource = LightSource( light );

    // obliczanie cosinusa k�ta odbicia �wiat�a
    float NdotL = dot( normal, TBN * lightSource.position.xyz );

    // obliczanie �wiat�a odbitego tylko dla powierzchni widocznej;
    // warto�� 0.0 k�ta odbicia oznacza, �e k�t odbicia jest w przedziale <0;90)
    if( NdotL > 0.0 )
        // ko�cowe obliczenie sk�adowych o�wietlenia
        return NdotL * diffuse * lightSource.diffuse;
    else
        // dla NdotL = 0.0 powierzchnia nie jest widoczna
        return vec4( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// �wiat�o punktowe w modelu Lamberta z przemieszczeniem
// wektora/kierunku �wiat�a
// light - numer �r�d�a �wiat�a
// normal - znormalizowany wektor normalny
// position - wsp�rz�dne wierzcho�ka
// po�o�enie �r�d�a �wiat�a lightSource[light].position.xyz musi by�
// wyra�one w tym samym uk�adzie wsp�rz�dnych co wektor normalny
// i wsp�rz�dne wierzcho�ka
// ambient - wsp�czynnik odbicia �wiat�a otoczenia; oznaczenie Ma
// diffuse - wsp�czynnik odbicia �wiat�a rozproszonego; oznaczenie Md
// TBN - macierz przekszta�cenia wektora/kierunku �wiat�a
//////////////////////////////////////////////////////////////////////
vec4 LambertPointLight( const int light, const vec3 normal, const vec3 position,
                        const vec4 ambient, const vec4 diffuse, const mat3 TBN )
{
    // pobranie parametr�w danego �r�d�a �wiat�a
    LightSourceParameters lightSource = LightSource( light );

    // wektor z bie��cego wierzcho�ka do �r�d�a �wiat�a - wektor kierunku �r�d�a �wiat�a
    vec3 lightVec = lightSource.position.xyz - position;

    // obliczenie odleg�o�ci od bie��cego wierzcho�ka do �r�d�a �wiat�a
    float distance = length( lightVec );

    // normalizacja wektora kierunku �r�d�a �wiat�a
    lightVec = TBN * normalize( lightVec );

    // obliczanie cosinusa k�ta odbicia �wiat�a
    float NdotL = dot( normal, lightVec );

    // obliczanie �wiat�a odbitego tylko dla powierzchni widocznej;
    // warto�� 0.0 k�ta odbicia oznacza, �e k�t odbicia jest w przedziale <0;90)
    if( NdotL > 0.0 )
    {
        // obliczenie wsp�czynnika t�umienia �wiat�a
        float att = 1.0 / ( lightSource.constantAttenuation +
                            lightSource.linearAttenuation * distance +
                            lightSource.quadraticAttenuation * distance * distance );

        // ko�cowe obliczenie sk�adowych o�wietlenia
        return att * ( LocalAmbientLight( light, ambient ) + NdotL * diffuse * lightSource.diffuse );
    }
    else
        // dla NdotL = 0.0 powierzchnia nie jest widoczna
        return vec4( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// o�wietlenie Lamberta z przemieszczeniem wektora/kierunku �wiat�a
// wymogi dotycz�ce parametr�w jak w opisach funkcji:
// LambertDirectionalLight i LambertPointLight
// TBN - macierz przekszta�cenia wektora/kierunku �wiat�a
//////////////////////////////////////////////////////////////////////
vec4 LambertLight( const int light, const vec3 normal, const vec3 position,
                    const vec4 ambient, const vec4 diffuse, const mat3 TBN )
{
    // �wiat�o kierunkowe
    if( LightSource( light ).position.w == 0.0 )
        return LambertDirectionalLight( light, normal, position, diffuse, TBN ) +
                LocalAmbientLight( light, ambient ) + GlobalAmbientLight( ambient );
    else
    // �wiat�o punktowe
        return LambertPointLight( light, normal, position, ambient, diffuse, TBN ) +
                GlobalAmbientLight( ambient );
}
