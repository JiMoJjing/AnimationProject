#pragma once
#include "Core.h"
#include <vector>
#include "Collision/CollisionComponent.h"

enum class NodeIndex : int
{
    TopLeft = 0,    // ��輱�� ��ġ�� �ʰ� ���� ����.
    TopRight,
    BottomRight,
    BottomLeft,
    Straddling,     // ��輱�� ��ģ ���.
    OutOfArea       // ������ ��� ���.
};

// ���� Ʈ�� ��� Ŭ����
class QuadTree;

// Bound Ŭ���� ��� ���� ���� �ݸ��� ���.
class Node
{
public:
    // ������.
    Node(CollisionComponent* bounds, int depth = 0);
    ~Node();

    // ��忡 ���� �߰��� �� ����ϴ� �Լ�.
    void Insert(Node* node);

    void Query(CollisionComponent* queryBounds, std::vector<Node*>& possibleNodes);

    void Clear();

    // Getter
    CollisionComponent* GetBounds() const { return bounds; }
    std::vector<Node*>& GetPoints() { return points; }

    Node* GetTopLeft() const { return topLeft; }
    Node* GetTopRight() const { return topRight; }
    Node* GetBottomRight() const { return bottomRight; }
    Node* GetBottomLeft() const { return bottomLeft; }

private:
    bool Subdivide();
    bool IsDivided();

    void ClearChildren();

    NodeIndex TestRegion(CollisionComponent* bounds);
    std::vector<NodeIndex> GetQuads(CollisionComponent* bounds);

    // ��� ����
    CollisionComponent* bounds;
    std::vector<Node*> points;

    // ����� ���� ����.
    int depth;

    // �ڽ� ���
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
};

// ���� Ʈ�� Ŭ����
class QuadTree
{
public:
    QuadTree(CollisionComponent* bounds);
    ~QuadTree();

    // ��Ʈ Ʈ���� ���� �߰��� �� ����ϴ� �Լ�.
    // ���ο����� ��Ʈ ��忡������ ��������� �߰�.
    void Insert(Node* node);

    std::vector<Node*> Query(Node* queryNode);

    // Getter
    Node* GetRoot() const { return root; }

public:
    // ���� �� �ִ� Ʈ���� �ִ� ����.
    static constexpr int MaxDepth = 3;

private:
    Node* root;
};