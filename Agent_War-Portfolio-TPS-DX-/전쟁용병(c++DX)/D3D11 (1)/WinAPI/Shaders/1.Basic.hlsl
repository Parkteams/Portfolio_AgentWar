//hlsl 쉐이더언어
//gpu에서 처리되는 연산을 작성하는 공간


struct VertexInput
{
    //                 시멘틱[n]
    float4 Position : POSITION0;
    float4 Color : COLOR0;
};
// PI
struct PixelInput
{
    float4 Position : SV_POSITION; //화면좌표계 포지션
    float4 Color : COLOR0;
};
cbuffer VS_W : register(b0) //register(b0) 이게 상수 b0위치
{
    row_major matrix World;
}
cbuffer VS_V : register(b1)
{
    row_major matrix View;
    row_major matrix Proj;
}
cbuffer VS_COLOR : register(b2)
{
    //4 개의 4바이트
    float4 Color;
}

//픽셀쉐이더 상수버퍼
cbuffer PS_LIGHT : register(b0)
{
    float2 ScreenPos; //스크린좌표
    float Radius; //반지름크기
    float Select; //남는값
    float4 LightColor; //조명 색
    float4 OutColor; //외곽 색
};


// in(Vertex)    VS    out(Vertex)
PixelInput VS(VertexInput input)
{
    //공간변환이 있을 예정인 곳
    PixelInput output;
    //L-W
    output.Position = mul(input.Position, World);
    //W-V
    output.Position = mul(output.Position, View);
    //V-P
    output.Position = mul(output.Position, Proj);
    
    
    
    
    
    output.Color =
    // sour     + dest
    //             0~1->   0~2   -1~1
    input.Color + (Color * 2.0f - 1.0f);

    //0~1을 넘어가는값이 되면 안됨
    saturate(output.Color);
    
    return output;
}
//->pixel  PS   ->color
//픽셀쉐이더 진입 함수
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET 은 타겟이될 색깔 
{
    float4 OutputColor;
    OutputColor = saturate(input.Color);
   
    //spotLight
    //                 픽셀의 좌표
    float2 Minus = input.Position.xy - ScreenPos;
    float dis = Minus.x * Minus.x + Minus.y * Minus.y;
    //sqrt는 제곱근 
    dis = sqrt(dis);
    if(Select == 0.0f)
    {
        if (dis > Radius)
        {
            return OutputColor + (OutColor * 2.0f - 1.0f);
        }
   
        return OutputColor + (LightColor * 2.0f - 1.0f);
    }
    if (Select == 1.0f)
    {
        //temp는 조명의 밝기
        //temp는 조명 가운데가 1 외곽으로 갈수록 0 조명 반지름경계에서부터 0
        float temp = 1.0f - saturate(dis / Radius);
        
        //기존색에 조명색을 입힌후
        OutputColor =
        OutputColor + (LightColor * 2.0f - 1.0f);
        saturate(OutputColor);
        //마지막결과에 명도로 곱
        OutputColor.rgb =
        OutputColor.rgb * temp;
        return OutputColor;
    }
    return OutputColor;
}