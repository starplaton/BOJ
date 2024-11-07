#include <bits/stdc++.h>
using namespace std;

// 구조체를 사용하여 AST 노드 정의
struct Node {
    enum Type { CONST,
                VAR,
                NOT,
                AND_OP,
                OR_OP } type;
    int value;    // CONST일 때 사용
    char var;     // VAR일 때 사용
    Node* child;  // NOT일 때 사용
    Node* left;   // AND, OR일 때 사용
    Node* right;  // AND, OR일 때 사용

    Node(Type t) : type(t), value(0), var(0), child(nullptr), left(nullptr), right(nullptr) {}
};

// 파서를 구현하는 클래스
class Parser {
   public:
    string expr;
    int pos;

    Parser(const string& s) : expr(s), pos(0) {}

    Node* parse_formula() {
        if (pos >= expr.size()) return nullptr;

        char current = expr[pos];
        if (current == '-') {
            pos++;  // '-' 연산자 소비
            Node* node = new Node(Node::NOT);
            node->child = parse_formula();
            return node;
        } else if (current == '(') {
            pos++;  // '(' 소비
            Node* left = parse_formula();
            if (pos >= expr.size()) return left;  // 예외 상황 처리
            char op = expr[pos];
            pos++;  // 연산자 소비
            Node* right = parse_formula();
            if (pos < expr.size() && expr[pos] == ')') pos++;  // ')' 소비
            Node* node;
            if (op == '*') {
                node = new Node(Node::AND_OP);
            } else {  // op == '+'
                node = new Node(Node::OR_OP);
            }
            node->left = left;
            node->right = right;
            return node;
        } else if (current == 'P' || current == 'Q' || current == 'R') {
            pos++;  // 변수 소비
            Node* node = new Node(Node::VAR);
            node->var = current;
            return node;
        } else if (current == '0' || current == '1' || current == '2') {
            pos++;  // 상수 소비
            Node* node = new Node(Node::CONST);
            node->value = current - '0';
            return node;
        }
        return nullptr;  // 예외 상황
    }
};

// 평가 함수를 구현
int evaluate(Node* node, int P, int Q, int R) {
    if (node->type == Node::CONST) {
        return node->value;
    }
    if (node->type == Node::VAR) {
        if (node->var == 'P') return P;
        if (node->var == 'Q') return Q;
        if (node->var == 'R') return R;
    }
    if (node->type == Node::NOT) {
        int child_val = evaluate(node->child, P, Q, R);
        if (child_val == 0) return 2;
        if (child_val == 1) return 1;
        if (child_val == 2) return 0;
    }
    if (node->type == Node::AND_OP) {
        int left_val = evaluate(node->left, P, Q, R);
        int right_val = evaluate(node->right, P, Q, R);
        // 클레니 논리의 AND는 min
        return min(left_val, right_val);
    }
    if (node->type == Node::OR_OP) {
        int left_val = evaluate(node->left, P, Q, R);
        int right_val = evaluate(node->right, P, Q, R);
        // 클레니 논리의 OR은 max
        return max(left_val, right_val);
    }
    return 0;  // 기본값
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    while (getline(cin, line)) {
        if (line == ".") break;
        // 파싱
        Parser parser(line);
        Node* root = parser.parse_formula();
        // 모든 (P,Q,R) 조합을 시험
        int count = 0;
        for (int P = 0; P <= 2; P++) {
            for (int Q = 0; Q <= 2; Q++) {
                for (int R = 0; R <= 2; R++) {
                    int val = evaluate(root, P, Q, R);
                    if (val == 2) count++;
                }
            }
        }
        cout << count << "\n";
    }
    return 0;
}
