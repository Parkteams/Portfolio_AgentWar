//hlsl ���̴����
//gpu���� ó���Ǵ� ������ �ۼ��ϴ� ����


struct VertexInput
{
    //                 �ø�ƽ[n]
    float4 Position : POSITION0;
    float4 Color : COLOR0;
};
// PI
struct PixelInput
{
    float4 Position : SV_POSITION; //ȭ����ǥ�� ������
    float4 Color : COLOR0;
};
cbuffer VS_W : register(b0) //register(b0) �̰� ��� b0��ġ
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
    //4 ���� 4����Ʈ
    float4 Color;
}

//�ȼ����̴� �������
cbuffer PS_LIGHT : register(b0)
{
    float2 ScreenPos; //��ũ����ǥ
    float Radius; //������ũ��
    float Select; //���°�
    float4 LightColor; //���� ��
    float4 OutColor; //�ܰ� ��
};


// in(Vertex)    VS    out(Vertex)
PixelInput VS(VertexInput input)
{
    //������ȯ�� ���� ������ ��
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

    //0~1�� �Ѿ�°��� �Ǹ� �ȵ�
    saturate(output.Color);
    
    return output;
}
//->pixel  PS   ->color
//�ȼ����̴� ���� �Լ�
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET �� Ÿ���̵� ���� 
{
    float4 OutputColor;
    OutputColor = saturate(input.Color);
   
    //spotLight
    //                 �ȼ��� ��ǥ
    float2 Minus = input.Position.xy - ScreenPos;
    float dis = Minus.x * Minus.x + Minus.y * Minus.y;
    //sqrt�� ������ 
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
        //temp�� ������ ���
        //temp�� ���� ����� 1 �ܰ����� ������ 0 ���� ��������迡������ 0
        float temp = 1.0f - saturate(dis / Radius);
        
        //�������� ������� ������
        OutputColor =
        OutputColor + (LightColor * 2.0f - 1.0f);
        saturate(OutputColor);
        //����������� ���� ��
        OutputColor.rgb =
        OutputColor.rgb * temp;
        return OutputColor;
    }
    return OutputColor;
}