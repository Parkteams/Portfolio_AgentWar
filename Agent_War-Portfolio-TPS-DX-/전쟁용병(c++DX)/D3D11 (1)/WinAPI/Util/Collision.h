#pragma once

//네모,네모
static bool isColRect(Object* ob1, Object* ob2);
//원,원
static bool isColCircle(Object* ob1, Object* ob2);
//네모,원
static bool isColRectCircle(Object* rc, Object* cc);
//원,점
static bool isColCirclePt(Object* ob, Vector2 pt);
//네모,점
static bool isColRectPt(Object* ob, Vector2 pt);
//회전네모,점
static bool isColRotRectPt(Object* ob, Vector2 pt);
//회전네모,원
static bool isColRotRectCircle(Object* rc, Object* cc);
//회전네모,회전네모
static bool isColRotRect(Object* ob1, Object* ob2);

//오브젝트,점
static bool isCollision(Object* ob, Vector2 pt)
{
    if (!ob->isActive) return false;

    if (ob->CollisionType == COL_RECT)
    {
        if(ob->Right == RIGHT)
        return isColRectPt(ob, pt);
        else
        return isColRotRectPt(ob, pt);
    }
    else if (ob->CollisionType == COL_CIRCLE)
    {
        return isColCirclePt(ob, pt);
    }
    return false;
}
//오브젝트 오브젝트
static bool isCollision(Object* ob1, Object* ob2)
{
    if (!ob1->isActive || !ob2->isActive) return false;

    if (ob1->CollisionType == COL_RECT)
    {
        if (ob2->CollisionType == COL_RECT)
        {
            if (ob1->Right != RIGHT ||
                ob2->Right != RIGHT)
            return isColRotRect(ob1, ob2);
            else
            return isColRect(ob1, ob2);
        }
        else
        {
            if (ob1->Right == RIGHT)
            return isColRectCircle(ob1, ob2);
            else
            return isColRotRectCircle(ob1, ob2);
        }
    }
    else if (ob1->CollisionType == COL_CIRCLE)
    {
        if (ob2->CollisionType == COL_CIRCLE)
        {
            return isColCircle(ob1, ob2);
        }
        else
        {
            if (ob2->Right == RIGHT)
                return isColRectCircle(ob2, ob1);
            else
                return isColRotRectCircle(ob2, ob1);
        }
    }
    return false;
}


static bool isColRect(Object* ob1, Object* ob2)
{
    //바뀐 포지션같은값으로 W갱신
    ob1->WorldUpdate();
    ob2->WorldUpdate();


    Vector2 pos1 = ob1->GetWorldPivot();
    Vector2 half1 = ob1->Scale * 0.5f;
    Vector2 pos2 = ob2->GetWorldPivot();
    Vector2 half2 = ob2->Scale * 0.5f;
    if (pos1.x - half1.x < pos2.x + half2.x &&
        pos1.x + half1.x > pos2.x - half2.x &&
        pos1.y - half1.y < pos2.y + half2.y &&
        pos1.y + half1.y > pos2.y - half2.y)
    {
        return true;
    }

    return false;
}

static bool isColCircle(Object* ob1, Object* ob2)
{
    //바뀐 포지션같은값으로 W갱신
    ob1->WorldUpdate();
    ob2->WorldUpdate();


    Vector2 pos1 = ob1->GetWorldPivot();
    Vector2 pos2 = ob2->GetWorldPivot();
    float half1 = ob1->Scale.x * 0.5f;
    float half2 = ob2->Scale.x * 0.5f;
    Vector2 Dis = pos1 - pos2;
    if (Dis.Length() < half1 + half2)
    {
        return true;
    }
    return false;
}


static bool isColRectPt(Object* ob, Vector2 pt)
{
    ob->WorldUpdate();


    Vector2 pos = ob->GetWorldPivot();
    Vector2 half = ob->Scale * 0.5f;

    if (pos.x - half.x < pt.x && pt.x < pos.x + half.x
        && pos.y - half.y < pt.y && pt.y < pos.y + half.y)
    {
        return true;
    }

    return false;
}

static bool isColCirclePt(Object* ob, Vector2 pt)
{
    ob->WorldUpdate();

    Vector2 Dis = ob->GetWorldPivot() - pt;
    float len = Dis.Length();
    if (len < ob->Scale.x * 0.5f)
    {
        return true;
    }

    return false;
}
//사각형과 원 충돌 (과제)
static bool isColRectCircle(Object* rc, Object* cc)
{
    rc->WorldUpdate();
    cc->WorldUpdate();

    Vector2 pos1 = rc->GetWorldPivot();
    Vector2 pos2 = cc->GetWorldPivot();

    //확장된 사각형에서 원의 중심점이 들어와 있는가?
    Object temp1, temp2;

    temp1 = *rc; //pos,scale 복사
    temp1.Pivot = OFFSET_N;
    temp1.Position = pos1;
    //양옆의사이즈를 원의 반지름만큼 확장
    temp1.Scale.x += cc->Scale.x;

    temp2 = *rc;//pos,scale 복사
    temp2.Pivot = OFFSET_N;
    temp2.Position = pos1;
    temp2.Scale.y += cc->Scale.x;

    if (isColRectPt(&temp1, pos2))
    {
        return true;
    }
    else if (isColRectPt(&temp2, pos2))
    {
        return true;
    }

    //사각형 꼭지점 4점 잡기
    Vector2 Vertex[4];
    Vector2 half = rc->Scale * 0.5f;
    Vertex[0] = pos1 - half;
    Vertex[1].x = pos1.x + half.x;
    Vertex[1].y = pos1.y - half.y;
    Vertex[2].x = pos1.x - half.x;
    Vertex[2].y = pos1.y + half.y;
    Vertex[3] = pos1 + half;
    for (int i = 0; i < 4; i++)
    {
        if (isColCirclePt(cc, Vertex[i]))
        {
            return true;
        }
    }
    return false;
}



static bool isColRotRectPt(Object* ob, Vector2 pt)
{
    ob->WorldUpdate();

    //                 역행렬반환함수
    Matrix inverse = ob->RT.Invert();

    //점이 오브젝트의 로컬로 이동
    //            v * mat;
    pt = Vector2::Transform(pt, inverse);


    Vector2 pos = Vector2::Transform(ob->Pivot, ob->S) ;
    Vector2 half = ob->Scale * 0.5f;

    if (pos.x - half.x < pt.x && pt.x < pos.x + half.x
        && pos.y - half.y < pt.y && pt.y < pos.y + half.y)
    {
        return true;
    }

    return false;
}

static bool isColRotRectCircle(Object* rc, Object* cc)
{
    rc->WorldUpdate();
    cc->WorldUpdate();

    Vector2 pos1 = Vector2::Transform(rc->Pivot, rc->S);
    Vector2 pos2 = cc->GetWorldPivot();
    Matrix inverse = rc->RT.Invert();
    pos2 = Vector2::Transform(pos2, inverse);

    //확장된 사각형에서 원의 중심점이 들어와 있는가?
    Object temp1, temp2;

    temp1 = *rc; //pos,scale 복사
    temp1.Pivot = OFFSET_N;
    temp1.Position = pos1;
    //양옆의사이즈를 원의 반지름만큼 확장
    temp1.Scale.x += cc->Scale.x;

    temp2 = *rc;//pos,scale 복사
    temp2.Pivot = OFFSET_N;
    temp2.Position = pos1;
    temp2.Scale.y += cc->Scale.x;

    if (isColRectPt(&temp1, pos2))
    {
        return true;
    }
    else if (isColRectPt(&temp2, pos2))
    {
        return true;
    }

    Object temp3;
    temp3 = *cc; //pos,scale 복사
    temp3.Pivot = OFFSET_N;
    temp3.Position = pos2;

    //사각형 꼭지점 4점 잡기
    Vector2 Vertex[4];
    Vector2 half = rc->Scale * 0.5f;
    Vertex[0] = pos1 - half;
    Vertex[1].x = pos1.x + half.x;
    Vertex[1].y = pos1.y - half.y;
    Vertex[2].x = pos1.x - half.x;
    Vertex[2].y = pos1.y + half.y;
    Vertex[3] = pos1 + half;
    for (int i = 0; i < 4; i++)
    {
        if (isColCirclePt(&temp3, Vertex[i]))
        {
            return true;
        }
    }
    return false;
}

static bool isColRotRect(Object* ob1, Object* ob2)
{
    ob1->WorldUpdate();
    ob2->WorldUpdate();
    //중심점
    Vector2 rc1Pos = ob1->GetWorldPivot();
    Vector2 rc2Pos = ob2->GetWorldPivot();
    //두 중심점간의 차이 벡터
    Vector2 Dis = rc1Pos - rc2Pos;

    //사각형마다 2개의 절반크기의 벡터

    Vector2 Rc1Up =
        ob1->Up * ob1->Scale.y * 0.5f;
    Vector2 Rc1Right =
        ob1->Right * ob1->Scale.x * 0.5f;

    Vector2 Rc2Up =
        ob2->Up * ob2->Scale.y * 0.5f;
    Vector2 Rc2Right =
        ob2->Right * ob2->Scale.x * 0.5f;

    //ob1의 right축 비교
    //       절대값(내적 a . b)
    float c = fabs(Dis.Dot(ob1->Right));

    //ob2에서 두벡터가 투영된 길이
    float a = fabs(Rc2Up.Dot(ob1->Right))
        + fabs(Rc2Right.Dot(ob1->Right));
    //ob1에서 두벡터가 투영된 길이
    float b = ob1->Scale.x * 0.5f;

    if (c > a + b)return false;

    //ob1의 Up축 비교
    //       절대값(내적 a . b)
    c = fabs(Dis.Dot(ob1->Up));

    //ob2에서 두벡터가 투영된 길이
    a = fabs(Rc2Up.Dot(ob1->Up))
        + fabs(Rc2Right.Dot(ob1->Up));
    //ob1에서 두벡터가 투영된 길이
    b = ob1->Scale.y * 0.5f;

    if (c > a + b)return false;

    //ob2의 Right축 비교
    //       절대값(내적 a . b)
    c = fabs(Dis.Dot(ob2->Right));

    //ob1에서 두벡터가 투영된 길이
    a = fabs(Rc1Up.Dot(ob2->Right))
        + fabs(Rc1Right.Dot(ob2->Right));
    //ob2에서 두벡터가 투영된 길이
    b = ob2->Scale.x * 0.5f;

    if (c > a + b)return false;

    //ob2의 Up축 비교
    //       절대값(내적 a . b)
    c = fabs(Dis.Dot(ob2->Up));

    //ob1에서 두벡터가 투영된 길이
    a = fabs(Rc1Up.Dot(ob2->Up))
        + fabs(Rc1Right.Dot(ob2->Up));
    //ob2에서 두벡터가 투영된 길이
    b = ob2->Scale.y * 0.5f;

    if (c > a + b)return false;

    return true;
}
