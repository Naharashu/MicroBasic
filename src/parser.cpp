#include "include/parser.h"
#include "include/analyzer.h"
#include "include/ast.h"
#include "include/lexer.h"
#include "include/table.h"
#include <memory>
#include <vector>

astptr parser::parse_factor() {
    token t = peek();
    if (t.type == token_type::L_BRACKET)
        return parse_expr();
    consume();
    return std::make_unique<ConstantNode>(t);
}

astptr parser::parse_pow() {
    astptr node = parse_factor();

    while (true) {
        token op = peek();
        if (op.type != token_type::AND_)
            break;

        consume();
        astptr rhs = parse_pow();
        node = std::make_unique<BinaryNode>(std::move(node), std::move(rhs), op);
    }

    return node;
}

astptr parser::parse_unary() {
    token op = peek();
    if (op.type == token_type::PLUS || op.type == token_type::MINUS || op.type == token_type::NOT) {
        consume();
        astptr unary = parse_pow();
        return std::make_unique<UnaryNode>(std::move(unary), op.type);
    }
    return parse_factor();
}

astptr parser::parse_and_b() {
    astptr node = parse_unary();

    while (true) {
        token op = peek();
        if (op.type != token_type::AND_)
            break;

        consume();
        astptr rhs = parse_unary();
        node = std::make_unique<BinaryNode>(std::move(node), std::move(rhs), op);
    }

    return node;
}

astptr parser::parse_xor() {
    astptr node = parse_and_b();

    while (true) {
        token op = peek();
        if (op.type != token_type::XOR)
            break;

        consume();
        astptr rhs = parse_and_b();
        node = std::make_unique<BinaryNode>(std::move(node), std::move(rhs), op);
    }

    return node;
}

astptr parser::parse_or_b() {
    astptr node = parse_xor();

    while (true) {
        token op = peek();
        if (op.type != token_type::OR_)
            break;

        consume();
        astptr rhs = parse_xor();
        node = std::make_unique<BinaryNode>(std::move(node), std::move(rhs), op);
    }

    return node;
}

astptr parser::parse_term() {
    astptr node = parse_or_b();

    while (true) {
        token op = peek();
        if (op.type != token_type::STAR && op.type != token_type::SLASH)
            break;

        consume();
        astptr rhs = parse_or_b();
        node = std::make_unique<BinaryNode>(std::move(node), std::move(rhs), op);
    }

    return node;
}

astptr parser::parse_expr() {
    astptr node = parse_term();

    while (true) {
        token op = peek();
        if (op.type != token_type::PLUS && op.type != token_type::MINUS)
            break;
        consume();
        astptr rhs = parse_term();
        node = std::make_unique<BinaryNode>(std::move(node), std::move(rhs), op);
    }
    return node;
}


astptr parser::parse_shift() {
    astptr node = parse_expr();
    while (true) {
        token op = peek();
        if (op.type != token_type::SHIFTR && op.type != token_type::SHIFTL)
            break;
        consume();
        astptr rhs = parse_expr();
        node = std::make_unique<CondNode>(std::move(node), std::move(rhs), op.type);
    }
    return node;
}

astptr parser::parse_cmp() {
    astptr node = parse_shift();
    while (true) {
        token op = peek();
        if (op.type != token_type::LESS && op.type != token_type::BIGGER && op.type != token_type::LE &&
            op.type != token_type::BE)
            break;
        consume();
        astptr rhs = parse_shift();
        node = std::make_unique<CondNode>(std::move(node), std::move(rhs), op.type);
    }
    return node;
}

astptr parser::parse_equal() {
    astptr node = parse_cmp();
    while (true) {
        token op = peek();
        if (op.type != token_type::EE && op.type != token_type::NE)
            break;
        consume();
        astptr rhs = parse_cmp();
        node = std::make_unique<CondNode>(std::move(node), std::move(rhs), op.type);
    }
    return node;
}

astptr parser::parse_assignment() {
    token c = peek();
    if (c.type == token_type::CONST) {
        consume();
        token id = peek();
        consume();
        analyzer.variable_const(id); // is variable already declared as const
        analyzer.isfunction(id);     // is trying like CONST PRINT X = 3
        if (analyzer.is_error) {
            sync();
            return nullptr;
        }

        consume_token(token_type::ID);

        consume_token(token_type::EQ);

        astptr value = parse_equal();

        consume_token(token_type::NEWLINE); // all statements end with Newline

        symbol var = {.name = id.id, .is_const = true, .val = 0, .reg = registers_allocated++};

        insert(var);

        return std::make_unique<AssignmentNode>(id.id, std::move(value));
    }
    consume_token(token_type::LET); // LET X = 3;
    token id = peek();
    consume();
    analyzer.variable_const(id); // is variable already declared as const
    analyzer.isfunction(id);     // is trying like CONST PRINT X = 3
    if (analyzer.is_error) {
        sync();
        return nullptr;
    }

    consume_token(token_type::ID);

    consume_token(token_type::EQ);

    astptr value = parse_equal();

    consume_token(token_type::NEWLINE); // all statements end with Newline

    symbol var = {.name = id.id, .is_const = true, .val = 0, .reg = registers_allocated++};

    insert(var);

    return std::make_unique<AssignmentNode>(id.id, std::move(value));
}

astptr parser::parse_statement() {
    token tok = peek();
    switch (tok.type) {
        case token_type::CONST:
        case token_type::LET:
            return parse_assignment();
        case token_type::NUMBER:
            return parse_factor();
        default:
            return parse_expr();
    }
}

std::vector<astptr> parser::parse() {
    std::vector<astptr> parsed;
    while (peek().type != token_type::EOF_) {
        parsed.emplace_back(parse_statement());
    }
    return parsed;
}
