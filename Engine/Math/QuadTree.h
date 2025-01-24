#pragma once
#include "Core.h"
#include <vector>
#include "Collision/CollisionComponent.h"

enum class NodeIndex : int
{
    TopLeft = 0,    // 경계선에 걸치지 않고 완전 포함.
    TopRight,
    BottomRight,
    BottomLeft,
    Straddling,     // 경계선에 걸친 경우.
    OutOfArea       // 영역을 벗어난 경우.
};

// 쿼드 트리 노드 클래스
class QuadTree;

// Bound 클래스 대신 내가 만든 콜리전 사용.
class Node
{
public:
    // 생성자.
    Node(CollisionComponent* bounds, int depth = 0);
    ~Node();

    // 노드에 점을 추가할 때 사용하는 함수.
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

    // 멤버 변수
    CollisionComponent* bounds;
    std::vector<Node*> points;

    // 노드의 현재 깊이.
    int depth;

    // 자식 노드
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
};

// 쿼드 트리 클래스
class QuadTree
{
public:
    QuadTree(CollisionComponent* bounds);
    ~QuadTree();

    // 쿼트 트리에 점을 추가할 때 사용하는 함수.
    // 내부에서는 루트 노드에서부터 재귀적으로 추가.
    void Insert(Node* node);

    std::vector<Node*> Query(Node* queryNode);

    // Getter
    Node* GetRoot() const { return root; }

public:
    // 나눌 수 있는 트리의 최대 깊이.
    static constexpr int MaxDepth = 3;

private:
    Node* root;
};