#ifndef _COMPILER_AST_HELPER_HPP
#define _COMPILER_AST_HELPER_HPP

#include "ast.hpp"

#include <string>

/************************************************************************/
/** {2 Helper functions for the AST}                                    */
/************************************************************************/
namespace Ast
{
    std::list<identifier> name_to_identifier_list(name_simple navn);
    std::list<identifier> name_to_identifier_list(name_qualified navn);
    std::list<identifier> name_to_identifier_list(const name* navn);

    /** {3 Converstion helpers} */
    /** Convert a name to its string representation */
    std::string name_to_string(const name* navn);

    /** {3 Predicate helpers} */
    template<typename INPUT, typename T>
        bool generic_test(const INPUT& input)
        {
            try
            {
                dynamic_cast<T&>(input);
                return true;
            }
            catch(std::bad_cast bc)
            {
                return false;
            }
        }

    template<typename T>
        bool generic_type_test(const type_expression& arg)
        {
            return generic_test<type_expression, T>(arg);
        }

    template<typename T>
        bool generic_type_test_base(const type_expression& t)
        {
            try
            {
                const type_expression_base& type = dynamic_cast<const type_expression_base&>(t);
                dynamic_cast<T&>(type);
                return true;
            }
            catch(std::bad_cast bc)
            {
                return false;
            }
        }

    /* typeexp -> bool */
    constexpr auto is_base_type   = generic_type_test<const type_expression_base>;
    constexpr auto is_array       = generic_type_test<const type_expression_tarray>;
    constexpr auto is_named_type  = generic_type_test<const type_expression_named>;

    constexpr auto is_void    = generic_type_test_base<const base_type_void>;
    constexpr auto is_byte    = generic_type_test_base<const base_type_byte>;
    constexpr auto is_short   = generic_type_test_base<const base_type_short>;
    constexpr auto is_int     = generic_type_test_base<const base_type_int>;
    //constexpr auto is_long    = generic_type_test_base<const base_type_long>;
    constexpr auto is_char    = generic_type_test_base<const base_type_char>;
    //constexpr auto is_float   = generic_type_test_base<const base_type_float>;
    //constexpr auto is_double  = generic_type_test_base<const base_type_double>;
    constexpr auto is_boolean = generic_type_test_base<const base_type_boolean>;

    /* exp -> bool */
    bool is_true_constant_throws(const expression& e);
    bool is_false_const(const expression& e);
    bool is_true_const(const expression& e);

    /* access -> bool */
    template<typename T>
        bool generic_access_test(const access& arg)
        {
            return generic_test<access, T>(arg);
        }

    constexpr auto is_public      = generic_access_test<const access_public>;
    constexpr auto is_protected   = generic_access_test<const access_protected>;

    /* decl -> bool */
    template<typename T>
        bool generic_declaration_test(const declaration& arg)
        {
            return generic_test<declaration, T>(arg);
        }

    constexpr auto is_field       = generic_declaration_test<const declaration_field>;
    constexpr auto is_method      = generic_declaration_test<const declaration_method>;
    constexpr auto is_constructor = generic_declaration_test<const declaration_constructor>;

    /* type_decl -> bool */
    template<typename T>
        bool generic_type_declaration_test(const type_declaration& arg)
        {
            return generic_test<type_declaration, T>(arg);
        }

    constexpr auto is_class       = generic_type_declaration_test<const type_declaration_class>;
    constexpr auto is_interface   = generic_type_declaration_test<const type_declaration_interface>;

    /** {3 Accessor helpers}  */
    std::string type_decl_name(const type_declaration& td);
    LexerPosition type_decl_pos(const type_declaration& td);
    std::string type_decl_kind(const type_declaration& td);
    std::string access_to_string(const access* ass);
    std::string base_type_to_string(const base_type* type);
    std::string unop_to_string(const unop* uno);
    std::string binop_to_string(const binop* bino);
}

#endif //_COMPILER_AST_HELPER_HPP
