import re


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
    elif (assignment.strip().startswith('"') and assignment.strip().endswith('"')) or (assignment.strip().startswith("'") and assignment.strip().endswith("'")):
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
    operators = ["+", "-", "*", "/", "%",  ">",
                 "<", "&", "|", "^", "~", "<<", ">>"]
    two_char_operators = ["**", "//", "==", "!=", ">=", "<=", "is", "or", "in"]
    three_char_operators = ["and", "not"]
    five_char_operators = ["is not", "not in"]

    types = []
    index = 0
    last = 0
    while index < len(assignment):
        char = assignment[index]
        if assignment[index : index + 5] in five_char_operators:
            types.append(assignment[last : index])
            last = index
            index += 5
        elif assignment[index : index + 3] in three_char_operators:
            types.append(assignment[last : index])
            last = index
            index += 3
        elif assignment[index : index + 2] in two_char_operators:
            types.append(assignment[last : index])
            last = index
            index += 2
        elif char in operators:
            types.append(assignment[last : index])
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


compile("test.py")
