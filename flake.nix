{
  description = "CMAKE/GLFW/GCC Development Environment Flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-25.05";
  };

  outputs = { self , nixpkgs ,... }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {
        inherit system;
    };
  in {
    devShells."${system}".default = pkgs.mkShell {
      # All dependencies that we'll need to build
      packages = with pkgs; [
        cmake
        gcc
        glfw
        glew
        libdecor
      ];
    };
  };
}
