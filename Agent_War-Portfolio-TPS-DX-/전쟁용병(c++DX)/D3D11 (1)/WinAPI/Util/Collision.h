#pragma once

//�׸�,�׸�
static bool isColRect(Object* ob1, Object* ob2);
//��,��
static bool isColCircle(Object* ob1, Object* ob2);
//�׸�,��
static bool isColRectCircle(Object* rc, Object* cc);
//��,��
static bool isColCirclePt(Object* ob, Vector2 pt);
//�׸�,��
static bool isColRectPt(Object* ob, Vector2 pt);
//ȸ���׸�,��
static bool isColRotRectPt(Object* ob, Vector2 pt);
//ȸ���׸�,��
static bool isColRotRectCircle(Object* rc, Object* cc);
//ȸ���׸�,ȸ���׸�
static bool isColRotRect(Object* ob1, Object* ob2);

//������Ʈ,��
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
//������Ʈ ������Ʈ
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
    //�ٲ� �����ǰ��������� W����
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
    //�ٲ� �����ǰ��������� W����
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
//�簢���� �� �浹 (����)
static bool isColRectCircle(Object* rc, Object* cc)
{
    rc->WorldUpdate();
    cc->WorldUpdate();

    Vector2 pos1 = rc->GetWorldPivot();
    Vector2 pos2 = cc->GetWorldPivot();

    //Ȯ��� �簢������ ���� �߽����� ���� �ִ°�?
    Object temp1, temp2;

    temp1 = *rc; //pos,scale ����
    temp1.Pivot = OFFSET_N;
    temp1.Position = pos1;
    //�翷�ǻ���� ���� ��������ŭ Ȯ��
    temp1.Scale.x += cc->Scale.x;

    temp2 = *rc;//pos,scale ����
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

    //�簢�� ������ 4�� ���
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

    //                 ����Ĺ�ȯ�Լ�
    Matrix inverse = ob->RT.Invert();

    //���� ������Ʈ�� ���÷� �̵�
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

    //Ȯ��� �簢������ ���� �߽����� ���� �ִ°�?
    Object temp1, temp2;

    temp1 = *rc; //pos,scale ����
    temp1.Pivot = OFFSET_N;
    temp1.Position = pos1;
    //�翷�ǻ���� ���� ��������ŭ Ȯ��
    temp1.Scale.x += cc->Scale.x;

    temp2 = *rc;//pos,scale ����
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
    temp3 = *cc; //pos,scale ����
    temp3.Pivot = OFFSET_N;
    temp3.Position = pos2;

    //�簢�� ������ 4�� ���
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
    //�߽���
    Vector2 rc1Pos = ob1->GetWorldPivot();
    Vector2 rc2Pos = ob2->GetWorldPivot();
    //�� �߽������� ���� ����
    Vector2 Dis = rc1Pos - rc2Pos;

    //�簢������ 2���� ����ũ���� ����

    Vector2 Rc1Up =
        ob1->Up * ob1->Scale.y * 0.5f;
    Vector2 Rc1Right =
        ob1->Right * ob1->Scale.x * 0.5f;

    Vector2 Rc2Up =
        ob2->Up * ob2->Scale.y * 0.5f;
    Vector2 Rc2Right =
        ob2->Right * ob2->Scale.x * 0.5f;

    //ob1�� right�� ��
    //       ���밪(���� a . b)
    float c = fabs(Dis.Dot(ob1->Right));

    //ob2���� �κ��Ͱ� ������ ����
    float a = fabs(Rc2Up.Dot(ob1->Right))
        + fabs(Rc2Right.Dot(ob1->Right));
    //ob1���� �κ��Ͱ� ������ ����
    float b = ob1->Scale.x * 0.5f;

    if (c > a + b)return false;

    //ob1�� Up�� ��
    //       ���밪(���� a . b)
    c = fabs(Dis.Dot(ob1->Up));

    //ob2���� �κ��Ͱ� ������ ����
    a = fabs(Rc2Up.Dot(ob1->Up))
        + fabs(Rc2Right.Dot(ob1->Up));
    //ob1���� �κ��Ͱ� ������ ����
    b = ob1->Scale.y * 0.5f;

    if (c > a + b)return false;

    //ob2�� Right�� ��
    //       ���밪(���� a . b)
    c = fabs(Dis.Dot(ob2->Right));

    //ob1���� �κ��Ͱ� ������ ����
    a = fabs(Rc1Up.Dot(ob2->Right))
        + fabs(Rc1Right.Dot(ob2->Right));
    //ob2���� �κ��Ͱ� ������ ����
    b = ob2->Scale.x * 0.5f;

    if (c > a + b)return false;

    //ob2�� Up�� ��
    //       ���밪(���� a . b)
    c = fabs(Dis.Dot(ob2->Up));

    //ob1���� �κ��Ͱ� ������ ����
    a = fabs(Rc1Up.Dot(ob2->Up))
        + fabs(Rc1Right.Dot(ob2->Up));
    //ob2���� �κ��Ͱ� ������ ����
    b = ob2->Scale.y * 0.5f;

    if (c > a + b)return false;

    return true;
}
