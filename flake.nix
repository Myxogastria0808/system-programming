{
  description = "clang flake sample";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    inputs:
    inputs.flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = inputs.nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            # C
            gcc
            # python
            python312
            python312Packages.legacy-cgi
            python312Packages.bleach
            python312Packages.mypy
          ];
        };
      }
    );
}
