###############################
####  TOKEN IDs FOR LEXER  ####
###############################

### NATIVES ###
T_NATIVE_INT = "INT"
T_NATIVE_FLOAT = "FLOAT"
T_NATIVE_STRING = "STRING"
T_NATIVE_LIST = "LIST"
T_NATIVE_DICT = "JSON_DICTIONARY"
T_NATIVE_TUPLE = "TUPLE"

### VARIABLE ###
T_VAR_DEF = "VAR_DEF"
T_VAR_TYPE = "VAR_TYPE"
T_VAR_ASSIGNMENT = "VAR_ASSIGNMENT"

### CONDITIONALS ###
T_IF = "IF"
T_ELIF = "ELSE_IF"
T_ELSE = "ELSE"
T_IS = "IS"
T_IN = "IN"
T_AND = "AND"
T_OR = "OR"
T_NOT = "NOT"

### LOOPS ###
T_WHILE = "WHILE"
T_FOR_IN = "FOR_IN"

### FUNCTION ###
T_FUNCTION_CALL = "FUNCTION_CALL"
T_FUNCTION_NAME = "FUNCTION_NAME"
T_FUNCTION_ARG = "FUNCTION_CALL_ARG"
T_FUNCTION_BODY = "FUNCTION_BODY"
T_FUNCTION_TYPE = "FUNCTION_TYPE"
T_FUNCTION_DEF_ARGS = "FUNCTION_ARGS"
T_FUNCTION_DEF = "FUNCTION_DEF"

### MISC ###
T_COMMENT = "COMMENT"
T_KEYWORD = "KEYWORD"
T_OPERATOR = "OPERATOR"
T_REF = "REFERENCE"
T_ROOT = "ROOT"
# Data - Do not iterate over this
T_DATA = "DATA"

### CLASSES ###
T_CLASS_DEF = "CLASS_DEF"
T_CLASS_SUPER = "CLASS_SUPER_EXTEND"
T_CLASS_EXTENSION = "CLASS_SUPER_EXTENTION"
T_MEMBER_FUNCTION = "MEMBER_FUNCTION"
T_CLASS_FUNCTION = "CLASS_FUNCTION"
T_CLASS_SELF = "CLASS_SELF"
T_CLASS_STATIC_VAR = "CLASS_STATIC_FUNCTION"
T_CLASS_STATIC_FUNCTION = "CLASS_STATIC_FUNCTION"


class Token:
    def __init__(self, type_, value=None):
        self.type = type_
        self.value = value

    def __repr__(self):
        if self.value:
            return f"{self.type}:{self.value}"
        return f"{self.type}"


class Lexer:
    pass


class SyntaxNode:
    def __init__(self, token, parent=None, children: list = None, new_line=False, semicolon=False, tab=False):
        self.parent = parent
        self.token: Token = token
        if children is None:
            self.children = []
        else:
            self.children: list = children

        self.new_line = new_line
        self.semicolon = semicolon
        self.tab = tab

    def add_child(self, node):
        self.children.append(node)
        node.parent = self

    def __repr__(self):
        return f"{self.token}"

    def __str__(self):
        return f"{self.token}"

    @property
    def serialize(self):
        return {
            "type": self.token.type,
            "value": self.token.value,
            "children": [child.serialize for child in self.children],
            "new_line": self.new_line,
            "semicolon": self.semicolon,
            "tab": self.tab
        }

    def iterate_tree(self, level=0, max_level=-1, include_data=False):
        node = self
        stack = [(node, level)]
        while len(stack) > 0:
            node, level = stack.pop()
            if node.token.type == T_DATA and not include_data:
                continue
            yield node, level

            if max_level != -1 and level > max_level:
                break
            for child in reversed(node.children):
                stack.append((child, level + 1))

    def print_tree(self, max_level=-1):
        for elem in self.iterate_tree(max_level=max_level, include_data=True):
            node, level = elem
            leading = ""
            if level > 0:
                leading = "\t" * level + "╚══"

            ending = ""
            if level > 0:
                ending = " "
            print(leading + ending + str(elem[0]))

    def parse(self):
        expression = self.token.value
        ignore_level = -1
        indent_level = 0
        indent_levels = []
        if expression is None:
            expression = ""
        if self.tab:
            indent_level += 1
            indent_levels.append(0)
        if self.semicolon:
            expression += ";"
        if self.new_line:
            expression += "\n"
        for elem in self.iterate_tree():
            node, level = elem
            if level == 0:
                continue
            if level <= ignore_level or ignore_level == -1:
                if type(node) == SyntaxNode:
                    if ignore_level != -1:
                        ignore_level = -1
                    if level in indent_levels:
                        indent_level -= 1
                        indent_levels.remove(level)
                    if node.tab:
                        indent_level += 1
                        indent_levels.append(indent_level)
                    val = node.token.value
                    if val is not None:
                        expression += " " + node.token.value
                        if node.semicolon:
                            expression += ";"
                        if node.new_line:
                            expression += "\n" + "\t" * indent_level
                else:
                    ignore_level = level
                    unindented_node_parsed = node.parse()
                    if unindented_node_parsed is not None:
                        indented = ""
                        for line in unindented_node_parsed.split("\n"):
                            indented += "\t" * indent_level + line + "\n"
                        indented = indented[:-1]
                        expression += " " + indented
                        if level in indent_levels:
                            indent_level -= 1
                            indent_levels.remove(level)
                        if node.tab:
                            indent_level += 1
                            indent_levels.append(indent_level)
                        if node.semicolon:
                            expression += ";"
                        if node.new_line:
                            expression += "\n" + "\t" * indent_level
        return expression


class VariableNode(SyntaxNode):
    def __init__(self, name, assignment: SyntaxNode, var_type="Any", parent=None, children: list = None):
        super().__init__(Token(T_VAR_DEF, name), parent, children, True, True)
        self.assignment = assignment
        self.type = var_type
        self.add_child(SyntaxNode(Token(T_VAR_TYPE, var_type)))
        self.add_child(assignment)

    def __repr__(self):
        return f"VarNode({self.token})"

    def __str__(self):
        return f"VarNode({self.token})"

    def parse(self):
        var_name = self.token.value
        assignment = self.assignment.parse().strip()

        if self.type is not None:
            return f"{self.type} {var_name} = {assignment}"

        return f"{var_name} = {assignment};"


class DataNode(SyntaxNode):
    def __init__(self, children: list, data=None, parent=None):
        super().__init__(Token(T_DATA, data), parent, children)
        self.data = data

    def parse(self):
        return ""


class FunctionDefArgumentNode(SyntaxNode):
    def __init__(self, name, arg_type="Any", parent=None):
        super().__init__(Token(T_FUNCTION_ARG, name), parent, children=[
            DataNode([
                SyntaxNode(Token(T_VAR_TYPE, arg_type))
            ])
        ],
                         new_line=False, semicolon=False)
        self.type = arg_type

    def __repr__(self):
        return f"FunctionArgNode({self.token.value})"

    def __str__(self):
        return f"FunctionArgNode({self.token.value})"

    def parse(self):
        arg_name = self.token.value
        if self.type is not None:
            return f"{self.type} {arg_name}"

        return arg_name


class FunctionNode(SyntaxNode):
    def __init__(self, funct_name, args: list, body: list, token_type=T_FUNCTION_DEF, return_type="void", parent=None):
        super().__init__(Token(token_type, funct_name), parent, new_line=True, semicolon=False, tab=True)
        self.args = args
        self.body = body
        self.return_type = return_type
        data = DataNode([])
        data.add_child(SyntaxNode(Token(T_FUNCTION_TYPE, return_type)))

        args = SyntaxNode(Token(T_FUNCTION_DEF_ARGS))
        for arg in self.args:
            args.add_child(arg)
        data.add_child(args)
        self.add_child(data)
        funct_body = SyntaxNode(Token(T_FUNCTION_BODY))
        for bodyNode in self.body:
            funct_body.add_child(bodyNode)
        self.add_child(funct_body)

    def __repr__(self):
        args = ""
        for arg in self.args:
            args += arg.parse() + ", "

        args = args[:-2]

        return f"{self.token.value}({args})"

    def __str__(self):
        args = ""
        for arg in self.args:
            args += arg.parse() + ", "

        args = args[:-2]

        return f"{self.token.value}({args})"

    def parse(self):
        args = ""
        for arg in self.args:
            args += arg.parse() + ", "

        args = args[:-2]

        body = ""

        ignore_level = -1
        indent_level = 1
        indent_levels = []
        should_tab = True

        for elem in self.iterate_tree():
            node, level = elem

            if level == 0:
                continue

            if level <= ignore_level or ignore_level == -1:
                if type(node) == SyntaxNode:
                    if ignore_level != -1:
                        ignore_level = -1
                    if level in indent_levels:
                        indent_level -= 1
                        indent_levels.remove(level)
                    if node.tab:
                        indent_level += 1
                        indent_levels.append(indent_level)
                    val = node.token.value
                    if val is not None:
                        if should_tab:
                            body += "\t" * indent_level + node.token.value
                            should_tab = False
                        else:
                            body += " " + node.token.value
                        if node.semicolon:
                            body += ";"
                        if node.new_line:
                            body += "\n"
                            should_tab = True
                else:
                    ignore_level = level
                    node_parsed = node.parse()
                    if node_parsed is not None:
                        indented = ""
                        for line in node_parsed.split("\n"):
                            indented += "\t" * indent_level + line + "\n"
                        indented = indented[:-1]
                        if should_tab:
                            body += indented
                            should_tab = False
                        else:
                            body += " " + indented
                        if level in indent_levels:
                            indent_level -= 1
                            indent_levels.remove(level)
                        if node.tab:
                            indent_level += 1
                            indent_levels.append(indent_level)
                        if node.semicolon:
                            body += ";"
                        if node.new_line:
                            body += "\n"
                            should_tab = True

        return f"{self.return_type} {self.token.value}({args})\n{{\n{body}}}"


class Parser:
    def __init__(self, nodes):
        self.nodes = nodes
        self.root = SyntaxNode(Token(T_ROOT))
        self.current_node = self.root

    def parse(self):
        lines = ""
        for node_elem in self.nodes:
            lines += node_elem.parse()
        return lines


def parse_variable(lines):
    var_name = ""
    assignment = ""
    var_type = ""

    open_parenthesis_count = 0
    close_parenthesis_count = 0

    full_definition = ""
    line_skip = 0

    for line in lines:
        open_parenthesis_count += line.count("(")
        close_parenthesis_count += line.count(")")

        full_definition += line
        line_skip += 1
        if open_parenthesis_count == close_parenthesis_count:
            break

    var_name_type: str = full_definition.split("=")[0]
    if ":" in var_name_type:
        var_name = var_name_type.split[0].strip()
        var_type = var_name_type.split[1].strip()
    else:
        var_name = var_name_type.strip()
        var_type = "any"

    assignment = '='.join(full_definition.split("=")[1:])
    return var_name, var_type, assignment, line_skip


def is_float(string: str):
    if string is None:
        return False
    try:
        float(string)
        return True
    except ValueError:
        return False


def parse_type(assignment: str):
    int_leads = ["0x", "0b", "0o"]
    if assignment.isdigit():
        return "int"
    elif is_float(assignment):
        return "float"
    elif (assignment.strip().startswith('"') and assignment.strip().endswith('"')) or (
            assignment.strip().startswith("'") and assignment.strip().endswith("'")):
        return "str"
    elif assignment.strip().startswith("[") and assignment.strip().endswith("]"):
        return "list"
    elif assignment.strip().startswith("{") and assignment.strip().endswith("}"):
        return "dict"
    elif assignment.strip().startswith("(") and assignment.strip().endswith(")"):
        return "tuple"
    elif assignment.endswith("j") and assignment[:-1].isdecimal():
        return "complex"


def parse_all_types(assignment: str):
    operators = ["+", "-", "*", "/", "%", ">",
                 "<", "&", "|", "^", "~", "<<", ">>"]
    two_char_operators = ["**", "//", "==", "!=", ">=", "<=", "is", "or", "in"]
    three_char_operators = ["and", "not"]
    five_char_operators = ["is not", "not in"]

    types = []
    index = 0
    last = 0
    while index < len(assignment):
        char = assignment[index]
        if assignment[index: index + 5] in five_char_operators:
            types.append(assignment[last: index])
            last = index
            index += 5
        elif assignment[index: index + 3] in three_char_operators:
            types.append(assignment[last: index])
            last = index
            index += 3
        elif assignment[index: index + 2] in two_char_operators:
            types.append(assignment[last: index])
            last = index
            index += 2
        elif char in operators:
            types.append(assignment[last: index])
            last = index
            index += 1
        else:
            index += 1

    return types


def compile(file_name):
    with open(file_name) as file:
        lines = file.readlines()

    functions = []
    variables = []
    local_variables = {}
    classes = []

    in_string = False

    includes = ["iostream"]

    include_files = []

    namespaces = ["std"]

    cpp_file = ""

    main = False

    is_variable = False

    main_function = ""

    line_skip = 0

    for line in lines:
        if line_skip > 0:
            line_skip -= 1
            continue
        line_stripped = line.strip()
        line_stripped.replace('\t', '')
        if line_stripped.startswith("input") and not in_string:
            if not '"PyUtils.h"' in includes:
                includes.append('"PyUtils.h"')
                include_files.append("impl\\PyUtils.h")
                include_files.append("impl\\PyUtils.cpp")
                namespaces.append("pyUtils")
            line_stripped = "pyInput" + line_stripped[5:] + ";"
            if not line.startswith("\t") and not line.startswith(" "):
                main_function += "\t" + line_stripped
            else:
                cpp_file += line_stripped
        elif not in_string:
            string_type = ""
            last_char = ""
            for charecter in line_stripped:
                if not in_string and charecter == "=":
                    var_parsed = parse_variable
                    # Parse variable
                if (charecter == '"' or charecter == "'") and not in_string:
                    in_string = True
                    if charecter == '"':
                        string_type = "double"
                    else:
                        string_type = "single"
                elif in_string and (charecter == '"' or charecter == "'") and last_char != "\\":
                    in_string = False
                    string_type = ""

                last_char = charecter

    with open("out.cpp", 'w') as file:
        head = ""
        for include in includes:
            head += "#include " + include + "\n"
        for f in include_files:
            with open(f) as f_impl:
                with open(f.replace("impl\\", ""), 'w') as f_api:
                    f_api.write(f_impl.read())
        head += "\n"
        for namespace in namespaces:
            head += "using namespace " + namespace + ";\n"

        head += "\nint main(int argc, char const *argv[]) {\n"
        head += main_function
        head += "\n}"

        cpp_file = head + cpp_file

        file.write(cpp_file)


function = FunctionNode("random_number", [FunctionDefArgumentNode("min"), FunctionDefArgumentNode("max")], [
    VariableNode("test_var", SyntaxNode(Token(T_VAR_ASSIGNMENT), children=[
        SyntaxNode(Token(T_NATIVE_TUPLE), children=[
            SyntaxNode(Token(T_NATIVE_INT, "1")),
            SyntaxNode(Token(T_NATIVE_INT, "2")),
            SyntaxNode(Token(T_NATIVE_INT, "3")),
            SyntaxNode(Token(T_NATIVE_INT, "4"))
        ])
    ]), "int"),
    VariableNode("rand", SyntaxNode(Token(T_VAR_ASSIGNMENT), children=[
        SyntaxNode(Token(T_FUNCTION_CALL), children=[
            SyntaxNode(Token(T_FUNCTION_NAME, "random.randint")),
            SyntaxNode(Token(T_NATIVE_INT, "0")),
            SyntaxNode(Token(T_NATIVE_INT, "5"))
        ])
    ]), "int"),
    SyntaxNode(Token(T_KEYWORD, "return"), children=[
        SyntaxNode(Token(T_REF, "rand"), new_line=True, semicolon=True)
    ])
], return_type="int")

function.print_tree()

print(function.parse())

# compile("test.py")
