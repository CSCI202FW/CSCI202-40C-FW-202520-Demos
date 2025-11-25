#ifndef BINARY_H
#define BINARY_H

template <class t>
struct binaryNode
{
    t *data;
    binaryNode<t> *lLink;
    binaryNode<t> *rLink;
    ~binaryNode() { delete data };
};

template <class t>
class binaryTreeType
{
public:
    const binaryTreeType<t> &operator=(const binaryTreeType<t> &otherTree);
    binaryTreeType(const binaryTreeType<t> &otherTree);
    binaryTreeType();

protected:
    binaryNode<t> *&getRoot();

private:
    binaryNode<t> root;
    void copyTree(binaryNode<t> *&copiedTreeRoot, binaryNode<t> *otherTreeRoot);
};

#endif

template <class t>
void binaryTreeType<t>::copyTree(binaryNode<t> *&currentNode, binaryNode<t> *copyFromNode)
{
    if (copyFromNode == nullptr)
    {
        currentNode = nullptr;
    }
    else
    {
        currentNode = new binaryNode<t>;
        currentNode->data = new t(*copyFromNode->data);
        copyTree(currentNode->lLink, copyFromNode->lLink);
        copyTree(currentNode->rLink, copyFromNode->rLink);
    }
}
