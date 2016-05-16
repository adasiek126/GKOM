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
// prototypy funkcji
//////////////////////////////////////////////////////////////////////
LightSourceParameters LightSource( const int light );
vec4 EyePosition();
vec4 GlobalAmbientLight( const vec4 ambient );
vec4 LocalAmbientLight( const int light, const vec4 ambient );

//////////////////////////////////////////////////////////////////////
// œwiat³o kierunkowe w modelu Blinna-Phonga
// light - numer Ÿród³a œwiat³a
// normal - znormalizowany wektor normalny
// position - wspó³rzêdne wierzcho³ka
// wektor kierunku œwiat³a lightSource[light].position.xyz musi byæ
// znormalizowany i wyra¿ony w tym samym uk³adzie wspó³rzêdnych co wektor
// normalny i wspó³rzêdne wierzcho³ka; ponadto wektor ten
// musi byæ zorientowany w kierunku do Ÿród³a œwiat³a
// diffuse - wspó³czynnik odbicia œwiat³a rozproszonego; oznaczenie Md
// specular - wspó³czynnik odbicia œwiat³a zwierciadlanego; oznaczenie Ms
// shininess - wyk³adnik wspó³czynnika funkcji rozb³ysku;
//             zakres wartoœci <0;128>; oznaczenie Msh
//////////////////////////////////////////////////////////////////////
vec4 BlinnPhongDirectionalLight( const int light, const vec3 normal, const vec3 position,
                                 const vec4 diffuse, const vec4 specular, const float shininess )
{
    // pobranie parametrów danego Ÿród³a œwiat³a
    LightSourceParameters lightSource = LightSource( light );

    // obliczanie cosinusa k¹ta odbicia œwiat³a
    float NdotL = dot( normal, lightSource.position.xyz );

    // obliczanie œwiat³a odbitego tylko dla powierzchni widocznej;
    // wartoœæ 0.0 k¹ta odbicia oznacza, ¿e k¹t odbicia jest w przedziale <0;90)
    if( NdotL > 0.0 )
    {
        // obliczanie wektora po³ówkowego - wektora pomiêdzy wektorem kierunku
        // œwiat³a i wektorem biegn¹cym od wierzcho³ka do obserwatora
        vec3 halfVec = normalize( lightSource.position.xyz + normalize( EyePosition().xyz - position ) );

        // obliczenie cosinusa k¹ta pomiêdzy wektorem normalnym i wektorem po³ówkowym
        float NdotH = max( dot( normal, halfVec ), 0.0 );

        // koñcowe obliczenie sk³adowych oœwietlenia
        return NdotL * diffuse * lightSource.diffuse +
                specular * lightSource.specular * pow( NdotH, shininess );
    }
    else
        // dla NdotL = 0.0 powierzchnia nie jest widoczna
        return vec4( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// œwiat³o punktowe w modelu Blinna-Phonga
// light - numer Ÿród³a œwiat³a
// normal - znormalizowany wektor normalny
// position - wspó³rzêdne wierzcho³ka
// po³o¿enie Ÿród³a œwiat³a lightSource[light].position.xyz musi byæ
// wyra¿one w tym samym uk³adzie wspó³rzêdnych co wektor normalny
// i wspó³rzêdne wierzcho³ka
// ambient - wspó³czynnik odbicia œwiat³a otoczenia; oznaczenie Ma
// diffuse - wspó³czynnik odbicia œwiat³a rozproszonego; oznaczenie Md
// specular - wspó³czynnik odbicia œwiat³a zwierciadlanego; oznaczenie Ms
// shininess - wyk³adnik wspó³czynnika funkcji rozb³ysku;
//             zakres wartoœci <0;128>; oznaczenie Msh
//////////////////////////////////////////////////////////////////////
vec4 BlinnPhongPointLight( const int light, const vec3 normal, const vec3 position,
                           const vec4 ambient, const vec4 diffuse, const vec4 specular,
                           const float shininess )
{
    // pobranie parametrów danego Ÿród³a œwiat³a
    LightSourceParameters lightSource = LightSource( light );

    // wektor z bie¿¹cego wierzcho³ka do Ÿród³a œwiat³a - wektor kierunku Ÿród³a œwiat³a
    vec3 lightVec = lightSource.position.xyz - position;

    // obliczenie odleg³oœci od bie¿¹cego wierzcho³ka do Ÿród³a œwiat³a
    float distance = length( lightVec );

    // normalizacja wektora kierunku Ÿród³a œwiat³a
    lightVec = normalize( lightVec );

    // obliczanie cosinusa k¹ta odbicia œwiat³a
    float NdotL = dot( normal, lightVec );

    // obliczanie œwiat³a odbitego tylko dla powierzchni widocznej;
    // wartoœæ 0.0 k¹ta odbicia oznacza, ¿e k¹t odbicia jest w przedziale <0;90)
    if( NdotL > 0.0 )
    {
        // obliczenie wspó³czynnika t³umienia œwiat³a
        float att = 1.0 / ( lightSource.constantAttenuation +
                            lightSource.linearAttenuation * distance +
                            lightSource.quadraticAttenuation * distance * distance );

        // obliczanie wektora po³ówkowego - wektora pomiêdzy wektorem kierunku
        // œwiat³a i wektorem biegn¹cym od wierzcho³ka do obserwatora
        vec3 halfVec = normalize( lightVec + normalize( EyePosition().xyz - position ) );

        // obliczenie cosinusa k¹ta pomiêdzy wektorem normalnym i wektorem po³ówkowym
        float NdotH = max( dot( normal, halfVec ), 0.0 );

        // koñcowe obliczenie sk³adowych oœwietlenia
        return att * ( LocalAmbientLight( light, ambient ) +
                NdotL * diffuse * lightSource.diffuse +
                specular * lightSource.specular * pow( NdotH, shininess ) );
    }
    else
        // dla NdotL = 0.0 powierzchnia nie jest widoczna
        return vec4( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// oœwietlenie Blinna-Phonga
// wymogi dotycz¹ce parametrów jak w opisach funkcji:
// BlinnPhongDirectionalLight i BlinnPhongPointLight
//////////////////////////////////////////////////////////////////////
vec4 BlinnPhongLight( const int light, const vec3 normal, const vec3 position,
                        const vec4 ambient, const vec4 diffuse,
                        const vec4 specular, const float shininess )
{
    // œwiat³o kierunkowe
    if( LightSource( light ).position.w == 0.0 )
        return BlinnPhongDirectionalLight( light, normal, position, diffuse, specular, shininess ) +
                LocalAmbientLight( light, ambient ) + GlobalAmbientLight( ambient );
    else
    // œwiat³o punktowe
        return BlinnPhongPointLight( light, normal, position, ambient, diffuse, specular, shininess ) +
                GlobalAmbientLight( ambient );
}

//////////////////////////////////////////////////////////////////////
// œwiat³o kierunkowe w modelu Blinna-Phonga z przemieszczeniem
// wektora/kierunku œwiat³a
// light - numer Ÿród³a œwiat³a
// normal - znormalizowany wektor normalny
// position - wspó³rzêdne wierzcho³ka
// wektor kierunku œwiat³a lightSource[light].position.xyz musi byæ
// znormalizowany i wyra¿ony w tym samym uk³adzie wspó³rzêdnych co wektor
// normalny i wspó³rzêdne wierzcho³ka; ponadto wektor ten
// musi byæ zorientowany w kierunku do Ÿród³a œwiat³a
// diffuse - wspó³czynnik odbicia œwiat³a rozproszonego; oznaczenie Md
// specular - wspó³czynnik odbicia œwiat³a zwierciadlanego; oznaczenie Ms
// shininess - wyk³adnik wspó³czynnika funkcji rozb³ysku;
//             zakres wartoœci <0;128>; oznaczenie Msh
// TBN - macierz przekszta³cenia wektora/kierunku œwiat³a
//////////////////////////////////////////////////////////////////////
vec4 BlinnPhongDirectionalLight( const int light, const vec3 normal, const vec3 position,
                                 const vec4 diffuse, const vec4 specular, const float shininess,
                                 const mat3 TBN )
{
    // pobranie parametrów danego Ÿród³a œwiat³a
    LightSourceParameters lightSource = LightSource( light );

    // obliczanie cosinusa k¹ta odbicia œwiat³a
    float NdotL = dot( normal, TBN * lightSource.position.xyz );

    // obliczanie œwiat³a odbitego tylko dla powierzchni widocznej;
    // wartoœæ 0.0 k¹ta odbicia oznacza, ¿e k¹t odbicia jest w przedziale <0;90)
    if( NdotL > 0.0 )
    {
        // obliczanie wektora po³ówkowego - wektora pomiêdzy wektorem kierunku
        // œwiat³a i wektorem biegn¹cym od wierzcho³ka do obserwatora
        vec3 halfVec = TBN * normalize( lightSource.position.xyz + normalize( EyePosition().xyz - position ) );

        // obliczenie cosinusa k¹ta pomiêdzy wektorem normalnym i wektorem po³ówkowym
        float NdotH = max( dot( normal, halfVec ), 0.0 );

        // koñcowe obliczenie sk³adowych oœwietlenia
        return NdotL * diffuse * lightSource.diffuse +
                specular * lightSource.specular * pow( NdotH, shininess );
    }
    else
        // dla NdotL = 0.0 powierzchnia nie jest widoczna
        return vec4( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// œwiat³o punktowe w modelu Blinna-Phonga z przemieszczeniem
// wektora/kierunku œwiat³a
// light - numer Ÿród³a œwiat³a
// normal - znormalizowany wektor normalny
// position - wspó³rzêdne wierzcho³ka
// po³o¿enie Ÿród³a œwiat³a lightSource[light].position.xyz musi byæ
// wyra¿one w tym samym uk³adzie wspó³rzêdnych co wektor normalny
// i wspó³rzêdne wierzcho³ka
// ambient - wspó³czynnik odbicia œwiat³a otoczenia; oznaczenie Ma
// diffuse - wspó³czynnik odbicia œwiat³a rozproszonego; oznaczenie Md
// specular - wspó³czynnik odbicia œwiat³a zwierciadlanego; oznaczenie Ms
// shininess - wyk³adnik wspó³czynnika funkcji rozb³ysku;
//             zakres wartoœci <0;128>; oznaczenie Msh
// TBN - macierz przekszta³cenia wektora/kierunku œwiat³a
//////////////////////////////////////////////////////////////////////
vec4 BlinnPhongPointLight( const int light, const vec3 normal, const vec3 position,
                           const vec4 ambient, const vec4 diffuse, const vec4 specular,
                           const float shininess, const mat3 TBN )
{
    // pobranie parametrów danego Ÿród³a œwiat³a
    LightSourceParameters lightSource = LightSource( light );

    // wektor z bie¿¹cego wierzcho³ka do Ÿród³a œwiat³a - wektor kierunku Ÿród³a œwiat³a
    vec3 lightVec = lightSource.position.xyz - position;

    // obliczenie odleg³oœci od bie¿¹cego wierzcho³ka do Ÿród³a œwiat³a
    float distance = length( lightVec );

    // normalizacja wektora kierunku Ÿród³a œwiat³a
    lightVec = TBN * normalize( lightVec );

    // obliczanie cosinusa k¹ta odbicia œwiat³a
    float NdotL = dot( normal, lightVec );

    // obliczanie œwiat³a odbitego tylko dla powierzchni widocznej;
    // wartoœæ 0.0 k¹ta odbicia oznacza, ¿e k¹t odbicia jest w przedziale <0;90)
    if( NdotL > 0.0 )
    {
        // obliczenie wspó³czynnika t³umienia œwiat³a
        float att = 1.0 / ( lightSource.constantAttenuation +
                            lightSource.linearAttenuation * distance +
                            lightSource.quadraticAttenuation * distance * distance );

        // obliczanie wektora po³ówkowego - wektora pomiêdzy wektorem kierunku
        // œwiat³a i wektorem biegn¹cym od wierzcho³ka do obserwatora
        vec3 halfVec = TBN * normalize( lightVec + normalize( EyePosition().xyz - position ) );

        // obliczenie cosinusa k¹ta pomiêdzy wektorem normalnym i wektorem po³ówkowym
        float NdotH = max( dot( normal, halfVec ), 0.0 );

        // koñcowe obliczenie sk³adowych oœwietlenia
        return att * ( LocalAmbientLight( light, ambient ) +
                NdotL * diffuse * lightSource.diffuse +
                specular * lightSource.specular * pow( NdotH, shininess ) );
    }
    else
        // dla NdotL = 0.0 powierzchnia nie jest widoczna
        return vec4( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// oœwietlenie Blinna-Phonga z przemieszczeniem wektora/kierunku œwiat³a
// wymogi dotycz¹ce parametrów jak w opisach funkcji:
// BlinnPhongDirectionalLight i BlinnPhongPointLight
// TBN - macierz przekszta³cenia wektora/kierunku œwiat³a
//////////////////////////////////////////////////////////////////////
vec4 BlinnPhongLight( const int light, const vec3 normal, const vec3 position,
                        const vec4 ambient, const vec4 diffuse,
                        const vec4 specular, const float shininess,
                        const mat3 TBN )
{
    // œwiat³o kierunkowe
    if( LightSource( light ).position.w == 0.0 )
        return BlinnPhongDirectionalLight( light, normal, position, diffuse, specular, shininess, TBN ) +
                LocalAmbientLight( light, ambient ) + GlobalAmbientLight( ambient );
    else
    // œwiat³o punktowe
        return BlinnPhongPointLight( light, normal, position, ambient, diffuse, specular, shininess, TBN ) +
                GlobalAmbientLight( ambient );
}
