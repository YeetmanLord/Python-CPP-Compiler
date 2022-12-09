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

    for line in lines:
        line_stripped = line.strip()
        line_stripped.replace('\t', '')
        if line_stripped.startswith("input") and not in_string:
            if not '"PyUtils.h"' in includes:
                includes.append('"PyUtils.h"')
                include_files.append("impl\\PyUtils.h")
                include_files.append("impl\\PyUtils.cpp")
                namespaces.append("pyUtils")
            line_stripped = "pyInput" + line_stripped[5:] + ";"
            if not line.startswith("\t"):
                main_function += "\t" + line_stripped
            else:
                cpp_file += line_stripped

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
