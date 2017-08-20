/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
//同时遍历两个链表，如果一个链表结束，则补0，同时，执行逐位加法时，要保存进位信息。这里创建链表的写法不好，因为最后会多出一个空节点，还要删掉它。
//time:42 ms
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int jinwei=0;
        int temp=0;
        int a,b=0;
        ListNode* result=new ListNode(0);
        ListNode* temp_node;
        ListNode* temp_node2;
        ListNode* last_node;
        temp_node=result;
        for(;l1!=NULL||l2!=NULL;)
        {
            a=(l1==NULL)?0:l1->val;
            b=(l2==NULL)?0:l2->val;
            temp=a+b+jinwei;
            temp_node->val=temp%10;
            jinwei=temp/10;
            l1=(l1==NULL)?NULL:l1->next;
            l2=(l2==NULL)?NULL:l2->next;
            
            //不使用空的头节点，在链表伸长时会比较麻烦
            temp_node2=new ListNode(0);
            temp_node->next=temp_node2;
            last_node=temp_node;
            temp_node=temp_node2;
        }
        if(jinwei!=0)
        {
            temp_node->val=jinwei;
        }
        else
        {
        	//不使用空头节点时，最后也会多出一个节点
            last_node->next=NULL;
            delete temp_node;
        }
        return result;
    }
};




/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
//更好的链表创建方法，一开始创建链表的头节点，但是头节点是不存数据的，他是一个守卫，之后的新节点都放置在当前最新节点的next上，这样最后就不会多出一个节点，中间也不需要更多临时变量
//time:38ms
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int jinwei=0;
        int temp=0;
        int a,b=0;
        ListNode* result=new ListNode(0);
        ListNode* temp_node;
        temp_node=result;
        for(;l1!=NULL||l2!=NULL;)
        {
        	//每次伸长链表，使用next来操作
            temp_node->next=new ListNode(0);
            a=(l1==NULL)?0:l1->val;
            b=(l2==NULL)?0:l2->val;
            temp=a+b+jinwei;
            temp_node->next->val=temp%10;
            jinwei=temp/10;
            l1=(l1==NULL)?NULL:l1->next;
            l2=(l2==NULL)?NULL:l2->next;
            //使用next就不需要一个中间变量来交换了
            temp_node=temp_node->next;
        }
        if(jinwei!=0)
        {
            temp_node->next=new ListNode(0);
            temp_node->next->val=jinwei;
        }
        //使用空头节点，最后也不会多出一个节点，但是要返回空节点的下一个节点，因为头节点相当于守卫
        return result->next;
    }
};
