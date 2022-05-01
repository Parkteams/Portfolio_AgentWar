#pragma once

class Int2
{
public:
    // l == r 
    int x;
    int y;
    Int2(int X = 0, int Y = 0) { x = X; y = Y; };
    //연산자 오버로딩
    bool operator ==(Int2 dest)
    {
        return (x == dest.x && y == dest.y);
    }
    bool operator !=(Int2 dest)
    {
        return (x != dest.x || y != dest.y);
        //return !(*this == dest);
    }
};

//선형보간
static Vector2 Lerp(Vector2 from, Vector2 to, float g)
{
    // g(0) -> from
    // g(1) -> from + to - from -> to
    return  from + (to - from) * g;
}

static Vector2 WorldToScreen(Vector2 CamPos,Vector2 pos)
{
    pos.x = pos.x - CamPos.x;
    pos.y = (float)WINSIZEY - (pos.y - CamPos.y);
    return pos;
}
static Vector2 ScreenToWorld(Vector2 CamPos,Vector2 pos)
{
    pos.x = pos.x + CamPos.x;
    pos.y = (float)WINSIZEY - pos.y + CamPos.y;

    return pos;
}

static float DirToRadian(Vector2 Dir)
{
    //만약 단위벡터가 아닐수도있으니까
    Dir.Normalize();
    float Seta;
    if (Dir.y < 0)
    {
        //          360.0*TORADIAN
        Seta = 2.0f * PI - acosf(Dir.x);
    }
    else
    {
        Seta = acosf(Dir.x);
    }
    return Seta;
}
static Vector2 RadianToDir(float Seta)
{
    return Vector2(cosf(Seta), sinf(Seta));
}

template <typename T>
static void MySwap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
};

template <typename T>
static void MyShuffle(T* arr, int range, int max)
{
    for (int i = 0; i < max; i++)
    {
        int dest = rand() % range;
        int sour = rand() % range;
        MySwap(arr[dest], arr[sour]);
    }
};
// start 에서 end까지 난수
// 100 ~ 200
// rand() % 101 - 0 ~ 100
// rand() % 101 + 100 - 100 ~ 200
static int RndInt(int start = 0, int end = 1)
{
    return rand() % (end - start + 1) + start;
};
//                          2.5                4.5   
static float RndFloat(float start = 0.0f, float end = 1.0f)
{
    return (float)rand() / (float)RAND_MAX * (end - start) + start;
};

//최소 최대값 정하기
template <typename T>// 700   0         600      
static T Saturate(T& in, T min = 0, T max = 1)
{
    if (in < min)
    {
        in = min;
        return min;
    }
    else if (in > max)
    {
        in = max;
        return max;
    }
    return in;
}

// 각도 조정
static float Degree_Under_2PI(float Rotation)
{
    if (Rotation > 2 * PI)
    {
        Rotation -= 2 * PI;
    }
    if (Rotation < 0.0f)
    {
        Rotation += 2 * PI;
    }
    return Rotation;
}


