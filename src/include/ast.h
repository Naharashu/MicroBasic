#ifndef B_AST_H
#define B_AST_H

#include "lexer.h"
#include <cstdint>
#include <memory>
#include <vector>

extern std::vector<uint8_t> generated;

enum class ast_kind : uint8_t {
    Constant,
    Binary,
    Unary,
    Condition,
    Assignment,
    Call,
    Label,
    IF,
    ELSE,
    WHILE,
    FOR,
    JUMP
};

struct ASTNode {
    virtual ~ASTNode() = default;
    virtual void gen();
    ast_kind kind;
};

using astptr = std::unique_ptr<ASTNode>;

struct ConstantNode : ASTNode {
    token tok;
    explicit ConstantNode(const token& t) : tok(t) {
        kind = ast_kind::Constant;
    }
    void gen() override;
};

struct BinaryNode : ASTNode {
    astptr left;
    astptr right;
    token op;
    BinaryNode(astptr l, astptr r, const token& op_) : left(std::move(l)), right(std::move(r)), op(op_) {
        kind = ast_kind::Binary;
    }
};

struct CondNode : ASTNode {
    astptr left;
    astptr right;
    token_type op;
    CondNode(astptr l, astptr r, const token_type& op_) : left(std::move(l)), right(std::move(r)), op(op_) {
        kind = ast_kind::Condition;
    }
};

struct UnaryNode : ASTNode {
    astptr left;
    token_type op;
    UnaryNode(astptr l, const token_type& op_) : left(std::move(l)), op(op_) {
        kind = ast_kind::Unary;
    }
};


#endif