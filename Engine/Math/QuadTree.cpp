#include "PreCompiledHeader.h"
#include "QuadTree.h"

Node::Node(CollisionComponent* bounds, int depth)
    : bounds(bounds), depth(depth),
    topLeft(nullptr), topRight(nullptr), bottomLeft(nullptr), bottomRight(nullptr)
{

}

Node::~Node()
{
    if (bounds->GetOwner() == nullptr)
    {
        SafeDelete(bounds);
    }
}

void Node::Insert(Node* node)
{
    // ��ġ�� ���� Ȯ��.
    NodeIndex result = TestRegion(node->GetBounds());

    // ��ġ�� ��쿡�� ���� ��忡 �߰�.
    if (result == NodeIndex::Straddling)
    {
        points.emplace_back(node);
    }

    // ��ġ�� �ʴ� ��쿡�� �����⸦ �����ϰ� �ڽ� ��忡 �߰�.
    else if (result != NodeIndex::OutOfArea)
    {
        //if (children.size() < MaxCapacity)
        if (Subdivide())
        {
            //children[(int)result]->Insert(point);
            if (result == NodeIndex::TopLeft)
            {
                topLeft->Insert(node);
            }
            else if (result == NodeIndex::TopRight)
            {
                topRight->Insert(node);
            }
            else if (result == NodeIndex::BottomRight)
            {
                bottomRight->Insert(node);
            }
            else if (result == NodeIndex::BottomLeft)
            {
                bottomLeft->Insert(node);
            }
        }

        // �� �̻� �ɰ� �� ������ ���� ��忡 �߰�.
        else
        {
            points.emplace_back(node);
        }
    }
}

void Node::Query(CollisionComponent* queryBounds, std::vector<Node*>& possibleNodes)
{
    possibleNodes.emplace_back(this);

    if (IsDivided())
    {
        std::vector<NodeIndex> quads = GetQuads(queryBounds);
        for (NodeIndex& index : quads)
        {
            if (index == NodeIndex::TopLeft)
            {
                topLeft->Query(queryBounds, possibleNodes);
            }
            else if (index == NodeIndex::TopRight)
            {
                topRight->Query(queryBounds, possibleNodes);
            }
            else if (index == NodeIndex::BottomRight)
            {
                bottomRight->Query(queryBounds, possibleNodes);
            }
            else if (index == NodeIndex::BottomLeft)
            {
                bottomLeft->Query(queryBounds, possibleNodes);
            }
        }
    }
}

void Node::Clear()
{
    for (Node* node : points)
    {
        SafeDelete(node);
    }

    points.clear();

    if (IsDivided())
    {
        topLeft->Clear();
        topRight->Clear();
        bottomRight->Clear();
        bottomLeft->Clear();

        ClearChildren();
    }
}

bool Node::Subdivide()
{
    // Ʈ������ ������ �ִ� ���̿� �����ϸ� ���̻� ������ ����.
    if (depth == QuadTree::MaxDepth)
    {
        return false;
    }

    if (!IsDivided())
    {
        int x = bounds->GetPosition().x;
        int y = bounds->GetPosition().y;
        int halfWidth = bounds->GetSize().x / 2;
        int halfHeight = bounds->GetSize().y / 2;

        topLeft = new Node(new CollisionComponent(x, y, halfWidth, halfHeight), depth + 1);
        topRight = new Node(new CollisionComponent(x + halfWidth, y, halfWidth, halfHeight), depth + 1);
        bottomRight = new Node(new CollisionComponent(x + halfWidth, y + halfHeight, halfWidth, halfHeight), depth + 1);
        bottomLeft = new Node(new CollisionComponent(x, y + halfHeight, halfWidth, halfHeight), depth + 1);
    }

    return true;
}

bool Node::IsDivided()
{
    return topLeft != nullptr;
}

void Node::ClearChildren()
{
    if (IsDivided())
    {
        SafeDelete(topLeft);
        SafeDelete(topRight);
        SafeDelete(bottomRight);
        SafeDelete(bottomLeft);
    }
}

NodeIndex Node::TestRegion(CollisionComponent* bounds)
{
    std::vector<NodeIndex> quads = GetQuads(bounds);

    if (quads.size() == 0)
    {
        return NodeIndex::OutOfArea;
    }

    if (quads.size() == 1)
    {
        return quads[0];
    }

    return NodeIndex::Straddling;
}

std::vector<NodeIndex> Node::GetQuads(CollisionComponent* bounds)
{
    std::vector<NodeIndex> quads;

    int x = this->bounds->GetPosition().x;
    int y = this->bounds->GetPosition().y;
    int halfWidth = this->bounds->GetSize().x / 2;
    int halfHeight = this->bounds->GetSize().y / 2;

    bool negativeX = bounds->GetPosition().x <= x + halfWidth;
    bool negativeY = bounds->GetPosition().y <= y + halfHeight;
    bool positiveX = bounds->GetMax().x >= x + halfWidth;
    bool positiveY = bounds->GetMax().y >= y + halfHeight;

    if (negativeX && negativeY)
    {
        quads.emplace_back(NodeIndex::TopLeft);
    }

    if (positiveX && negativeY)
    {
        quads.emplace_back(NodeIndex::TopRight);
    }

    if (positiveX && positiveY)
    {
        quads.emplace_back(NodeIndex::BottomRight);
    }

    if (negativeX && positiveY)
    {
        quads.emplace_back(NodeIndex::BottomLeft);
    }

    return quads;
}

QuadTree::QuadTree(CollisionComponent* bounds)
{
    root = new Node(bounds);
}

QuadTree::~QuadTree()
{
    // ��������� ��Ʈ�� �ڼ� ��� ����.
    root->Clear();

    // ��Ʈ ��� ����.
    SafeDelete(root);
}

void QuadTree::Insert(Node* node)
{
    root->Insert(node);
}

std::vector<Node*> QuadTree::Query(Node* queryNode)
{
    std::vector<Node*> possibleNodes;
    root->Query(queryNode->GetBounds(), possibleNodes);

    std::vector<Node*> intersects;
    for (Node* node : possibleNodes)
    {
        // ����� ���� �ڵ� ( �˻��ؼ� �浹 �� ��常 ������ ).
        //for (Node* point : node->GetPoints())
        //{
        //    if (point->GetBounds()->Intersect(queryNode->GetBounds()))
        //    {
        //        intersects.emplace_back(point);
        //    }
        //}

        // �˻� ��尡 ���Ե� ��� ��尡 ������ �ִ� ���� ��� ������.
        if (node->GetBounds()->Intersect(queryNode->GetBounds()))
        {
            std::vector<Node*> points = node->GetPoints();
            intersects.insert(intersects.end(), points.begin(), points.end());
        }
    }


    return intersects;
}
