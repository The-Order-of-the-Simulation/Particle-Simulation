
{
  description = "A flake for building Particle-Simulation";
  inputs = {
    nixpkgs = {
      url = "nixpkgs/nixos-21.05";
    };
    flake-utils = {
      url = "github:numtide/flake-utils";
    };
  };

  outputs = { nixpkgs, flake-utils, ... }: flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs {
        inherit system;
      };
      particle-simulation = (with pkgs; stdenv.mkDerivation {
          pname = "Particle-Simulation";
          version = "1.0.0";
          src = ./.;
          nativeBuildInputs = [
            gcc
            glm
          ];
          buildPhase = "g++ -march=native -Ofast -s -pthread -Wall -Wextra main.cpp -o simulation";
          installPhase = ''
            mkdir -p $out/bin
            mv simulation $out/bin
          '';
        }
      );
    in rec {
      defaultApp = flake-utils.lib.mkApp {
        drv = defaultPackage;
      };
      defaultPackage = particle-simulation;
      devShell = pkgs.mkShell {
        buildInputs = [
          particle-simulation
        ];
      };
    }      
  );
}
