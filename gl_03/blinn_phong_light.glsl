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
vec4 EyePosition();
vec4 GlobalAmbientLight( const vec4 ambient );
vec4 LocalAmbientLight( const int light, const vec4 ambient );

//////////////////////////////////////////////////////////////////////
// �wiat�o kierunkowe w modelu Blinna-Phonga
// light - numer �r�d�a �wiat�a
// normal - znormalizowany wektor normalny
// position - wsp�rz�dne wierzcho�ka
// wektor kierunku �wiat�a lightSource[light].position.xyz musi by�
// znormalizowany i wyra�ony w tym samym uk�adzie wsp�rz�dnych co wektor
// normalny i wsp�rz�dne wierzcho�ka; ponadto wektor ten
// musi by� zorientowany w kierunku do �r�d�a �wiat�a
// diffuse - wsp�czynnik odbicia �wiat�a rozproszonego; oznaczenie Md
// specular - wsp�czynnik odbicia �wiat�a zwierciadlanego; oznaczenie Ms
// shininess - wyk�adnik wsp�czynnika funkcji rozb�ysku;
//             zakres warto�ci <0;128>; oznaczenie Msh
//////////////////////////////////////////////////////////////////////
vec4 BlinnPhongDirectionalLight( const int light, const vec3 normal, const vec3 position,
                                 const vec4 diffuse, const vec4 specular, const float shininess )
{
    // pobranie parametr�w danego �r�d�a �wiat�a
    LightSourceParameters lightSource = LightSource( light );

    // obliczanie cosinusa k�ta odbicia �wiat�a
    float NdotL = dot( normal, lightSource.position.xyz );

    // obliczanie �wiat�a odbitego tylko dla powierzchni widocznej;
    // warto�� 0.0 k�ta odbicia oznacza, �e k�t odbicia jest w przedziale <0;90)
    if( NdotL > 0.0 )
    {
        // obliczanie wektora po��wkowego - wektora pomi�dzy wektorem kierunku
        // �wiat�a i wektorem biegn�cym od wierzcho�ka do obserwatora
        vec3 halfVec = normalize( lightSource.position.xyz + normalize( EyePosition().xyz - position ) );

        // obliczenie cosinusa k�ta pomi�dzy wektorem normalnym i wektorem po��wkowym
        float NdotH = max( dot( normal, halfVec ), 0.0 );

        // ko�cowe obliczenie sk�adowych o�wietlenia
        return NdotL * diffuse * lightSource.diffuse +
                specular * lightSource.specular * pow( NdotH, shininess );
    }
    else
        // dla NdotL = 0.0 powierzchnia nie jest widoczna
        return vec4( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// �wiat�o punktowe w modelu Blinna-Phonga
// light - numer �r�d�a �wiat�a
// normal - znormalizowany wektor normalny
// position - wsp�rz�dne wierzcho�ka
// po�o�enie �r�d�a �wiat�a lightSource[light].position.xyz musi by�
// wyra�one w tym samym uk�adzie wsp�rz�dnych co wektor normalny
// i wsp�rz�dne wierzcho�ka
// ambient - wsp�czynnik odbicia �wiat�a otoczenia; oznaczenie Ma
// diffuse - wsp�czynnik odbicia �wiat�a rozproszonego; oznaczenie Md
// specular - wsp�czynnik odbicia �wiat�a zwierciadlanego; oznaczenie Ms
// shininess - wyk�adnik wsp�czynnika funkcji rozb�ysku;
//             zakres warto�ci <0;128>; oznaczenie Msh
//////////////////////////////////////////////////////////////////////
vec4 BlinnPhongPointLight( const int light, const vec3 normal, const vec3 position,
                           const vec4 ambient, const vec4 diffuse, const vec4 specular,
                           const float shininess )
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

        // obliczanie wektora po��wkowego - wektora pomi�dzy wektorem kierunku
        // �wiat�a i wektorem biegn�cym od wierzcho�ka do obserwatora
        vec3 halfVec = normalize( lightVec + normalize( EyePosition().xyz - position ) );

        // obliczenie cosinusa k�ta pomi�dzy wektorem normalnym i wektorem po��wkowym
        float NdotH = max( dot( normal, halfVec ), 0.0 );

        // ko�cowe obliczenie sk�adowych o�wietlenia
        return att * ( LocalAmbientLight( light, ambient ) +
                NdotL * diffuse * lightSource.diffuse +
                specular * lightSource.specular * pow( NdotH, shininess ) );
    }
    else
        // dla NdotL = 0.0 powierzchnia nie jest widoczna
        return vec4( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// o�wietlenie Blinna-Phonga
// wymogi dotycz�ce parametr�w jak w opisach funkcji:
// BlinnPhongDirectionalLight i BlinnPhongPointLight
//////////////////////////////////////////////////////////////////////
vec4 BlinnPhongLight( const int light, const vec3 normal, const vec3 position,
                        const vec4 ambient, const vec4 diffuse,
                        const vec4 specular, const float shininess )
{
    // �wiat�o kierunkowe
    if( LightSource( light ).position.w == 0.0 )
        return BlinnPhongDirectionalLight( light, normal, position, diffuse, specular, shininess ) +
                LocalAmbientLight( light, ambient ) + GlobalAmbientLight( ambient );
    else
    // �wiat�o punktowe
        return BlinnPhongPointLight( light, normal, position, ambient, diffuse, specular, shininess ) +
                GlobalAmbientLight( ambient );
}

//////////////////////////////////////////////////////////////////////
// �wiat�o kierunkowe w modelu Blinna-Phonga z przemieszczeniem
// wektora/kierunku �wiat�a
// light - numer �r�d�a �wiat�a
// normal - znormalizowany wektor normalny
// position - wsp�rz�dne wierzcho�ka
// wektor kierunku �wiat�a lightSource[light].position.xyz musi by�
// znormalizowany i wyra�ony w tym samym uk�adzie wsp�rz�dnych co wektor
// normalny i wsp�rz�dne wierzcho�ka; ponadto wektor ten
// musi by� zorientowany w kierunku do �r�d�a �wiat�a
// diffuse - wsp�czynnik odbicia �wiat�a rozproszonego; oznaczenie Md
// specular - wsp�czynnik odbicia �wiat�a zwierciadlanego; oznaczenie Ms
// shininess - wyk�adnik wsp�czynnika funkcji rozb�ysku;
//             zakres warto�ci <0;128>; oznaczenie Msh
// TBN - macierz przekszta�cenia wektora/kierunku �wiat�a
//////////////////////////////////////////////////////////////////////
vec4 BlinnPhongDirectionalLight( const int light, const vec3 normal, const vec3 position,
                                 const vec4 diffuse, const vec4 specular, const float shininess,
                                 const mat3 TBN )
{
    // pobranie parametr�w danego �r�d�a �wiat�a
    LightSourceParameters lightSource = LightSource( light );

    // obliczanie cosinusa k�ta odbicia �wiat�a
    float NdotL = dot( normal, TBN * lightSource.position.xyz );

    // obliczanie �wiat�a odbitego tylko dla powierzchni widocznej;
    // warto�� 0.0 k�ta odbicia oznacza, �e k�t odbicia jest w przedziale <0;90)
    if( NdotL > 0.0 )
    {
        // obliczanie wektora po��wkowego - wektora pomi�dzy wektorem kierunku
        // �wiat�a i wektorem biegn�cym od wierzcho�ka do obserwatora
        vec3 halfVec = TBN * normalize( lightSource.position.xyz + normalize( EyePosition().xyz - position ) );

        // obliczenie cosinusa k�ta pomi�dzy wektorem normalnym i wektorem po��wkowym
        float NdotH = max( dot( normal, halfVec ), 0.0 );

        // ko�cowe obliczenie sk�adowych o�wietlenia
        return NdotL * diffuse * lightSource.diffuse +
                specular * lightSource.specular * pow( NdotH, shininess );
    }
    else
        // dla NdotL = 0.0 powierzchnia nie jest widoczna
        return vec4( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// �wiat�o punktowe w modelu Blinna-Phonga z przemieszczeniem
// wektora/kierunku �wiat�a
// light - numer �r�d�a �wiat�a
// normal - znormalizowany wektor normalny
// position - wsp�rz�dne wierzcho�ka
// po�o�enie �r�d�a �wiat�a lightSource[light].position.xyz musi by�
// wyra�one w tym samym uk�adzie wsp�rz�dnych co wektor normalny
// i wsp�rz�dne wierzcho�ka
// ambient - wsp�czynnik odbicia �wiat�a otoczenia; oznaczenie Ma
// diffuse - wsp�czynnik odbicia �wiat�a rozproszonego; oznaczenie Md
// specular - wsp�czynnik odbicia �wiat�a zwierciadlanego; oznaczenie Ms
// shininess - wyk�adnik wsp�czynnika funkcji rozb�ysku;
//             zakres warto�ci <0;128>; oznaczenie Msh
// TBN - macierz przekszta�cenia wektora/kierunku �wiat�a
//////////////////////////////////////////////////////////////////////
vec4 BlinnPhongPointLight( const int light, const vec3 normal, const vec3 position,
                           const vec4 ambient, const vec4 diffuse, const vec4 specular,
                           const float shininess, const mat3 TBN )
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

        // obliczanie wektora po��wkowego - wektora pomi�dzy wektorem kierunku
        // �wiat�a i wektorem biegn�cym od wierzcho�ka do obserwatora
        vec3 halfVec = TBN * normalize( lightVec + normalize( EyePosition().xyz - position ) );

        // obliczenie cosinusa k�ta pomi�dzy wektorem normalnym i wektorem po��wkowym
        float NdotH = max( dot( normal, halfVec ), 0.0 );

        // ko�cowe obliczenie sk�adowych o�wietlenia
        return att * ( LocalAmbientLight( light, ambient ) +
                NdotL * diffuse * lightSource.diffuse +
                specular * lightSource.specular * pow( NdotH, shininess ) );
    }
    else
        // dla NdotL = 0.0 powierzchnia nie jest widoczna
        return vec4( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// o�wietlenie Blinna-Phonga z przemieszczeniem wektora/kierunku �wiat�a
// wymogi dotycz�ce parametr�w jak w opisach funkcji:
// BlinnPhongDirectionalLight i BlinnPhongPointLight
// TBN - macierz przekszta�cenia wektora/kierunku �wiat�a
//////////////////////////////////////////////////////////////////////
vec4 BlinnPhongLight( const int light, const vec3 normal, const vec3 position,
                        const vec4 ambient, const vec4 diffuse,
                        const vec4 specular, const float shininess,
                        const mat3 TBN )
{
    // �wiat�o kierunkowe
    if( LightSource( light ).position.w == 0.0 )
        return BlinnPhongDirectionalLight( light, normal, position, diffuse, specular, shininess, TBN ) +
                LocalAmbientLight( light, ambient ) + GlobalAmbientLight( ambient );
    else
    // �wiat�o punktowe
        return BlinnPhongPointLight( light, normal, position, ambient, diffuse, specular, shininess, TBN ) +
                GlobalAmbientLight( ambient );
}
