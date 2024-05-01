#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* dummy = new ListNode();
    ListNode* curr = dummy;

    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val < list2->val) {
            curr->next = list1;
            list1 = list1->next;
        } else {
            curr->next = list2;
            list2 = list2->next;
        }
        curr = curr->next;
    }

    if (list1 != nullptr) {
        curr->next = list1;
    } else {
        curr->next = list2;
    }

    ListNode* result = dummy->next;
    delete dummy;
    return result;
}


ListNode* createList1() {
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(4);

    node1->next = node2;
    node2->next = node3;

    return node1;
}

ListNode* createList2() {
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(3);
    ListNode* node3 = new ListNode(4);

    node1->next = node2;
    node2->next = node3;

    return node1;
}

int main() {
    ListNode* node1 = createList1();
    ListNode* node2 = createList2();
    ListNode* node_result = mergeTwoLists(node1, node2);

    while (node_result != nullptr) {
        // Доступ к значению текущего узла
        int value = node_result->val;
        // Доступ к следующему узлу
        ListNode* nextNode = node_result->next;

        // Вывод значения текущего узла
        std::cout << value << " ";

        // Переход к следующему узлу
        node_result = nextNode;
    }
}