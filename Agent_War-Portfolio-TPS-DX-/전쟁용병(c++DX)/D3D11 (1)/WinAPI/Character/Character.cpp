#include "stdafx.h"
#include "Character.h"

Character::Character()
{
    MoveDir = Vector2(1.0f, 0.0f);
    Root = new ObRect();
    Root->isFill = false;

}

Character::~Character()
{
    delete Root;
}

void Character::Render()
{
    Root->Render();
}

Vector2 Character::GetPos()
{
    return Root->GetWorldPos();
}

float Character::GetRotate()
{
    return Root->Rotation.z;
}

void Character::SetPos(Vector2 pos)
{
    Root->Position = pos;
    Selected_Pos = pos;
}

void Character::SetPosX(Vector2 pos)
{
    Root->Position.x = pos.x;
}

void Character::SetPosY(Vector2 pos)
{
    Root->Position.y = pos.y;
}

void Character::Rotate_Root(float Rotation)
{
    Root->Rotation.z = Rotation;
}

void Character::LookTarget(Vector2 target, ObImage* img, float Rotation)
{
    Vector2 Dis = target - Root->Position;
    float Angle = DirToRadian(Dis) - PI / 2.0f + Rotation;
    img->Rotation.z = Angle;
}

void Character::LookTarget2(Vector2 target, ObImage* img, float Rotation)
{
    Vector2 Dis = target - Root->Position;
    float Angle = DirToRadian(Dis) + PI / 2.0f + Rotation;
    img->Rotation.z = Angle;
}

bool Character::Range(Vector2 target, ObLine* line1, ObLine* line2, float Rotation,float Rotation2)
{
    float Radian = DirToRadian(target - Root->Position) - Rotation;
    if (((Radian < line2->Rotation.z) and (Radian > line1->Rotation.z)) or
        (line1->Rotation.z > (2 * PI - Rotation2 * TORADIAN - Rotation) and ((line1->Rotation.z + Rotation) < DirToRadian(target - Root->Position) or (line2->Rotation.z + Rotation) > DirToRadian(target - Root->Position))))
    {
        return true;
    }
    else
    {
        return false;
    }
}
