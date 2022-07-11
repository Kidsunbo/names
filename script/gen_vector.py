def generate(input_name, output_name, container_name):
    with open(output_name, "w") as output_file, open(input_name, 'r') as input_file:
        items = [f'"{item.strip()}"' for item in input_file.readlines() if item.strip() != ""]
        output_file.write(f"inline std::vector {container_name} = {{ {','.join(items)} }};")

generate("./data/adjective.words", "./include/adjective.hpp", 'adjective')
generate("./data/noun.words", "./include/noun.hpp", "noun")