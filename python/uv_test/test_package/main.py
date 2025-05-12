from .module_a import module_a_func, module_var_a
from .module_b import Module_B, module_var_b


def main():
    print(module_var_a)
    module_a_func()
    print(module_var_b)
    print(Module_B())
    print(module_var_a)


if __name__ == "__main__":
    main()
