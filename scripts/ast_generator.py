import argparse


def defineAst(outputDirectory, classname, expression_list):
    path = outputDirectory + "/" + classname + ".h"
    pass


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--outputDirectory", help="output directory")
    args = parser.parse_args()

    outputDirectory = args.outputDirectory
    if not outputDirectory:
        print("Usage: ast_generator.py <output directory>")
    else:
        outputDirectory: str
        defineAst(
            outputDirectory,
            "Expr",
            [
                "Binary   : Expr left, Token operator, Expr right",
                "Grouping : Expr expression",
                "Literal  : Object value",
                "Unary    : Token operator, Expr right",
            ],
        )


if __name__ == "__main__":
    main()
