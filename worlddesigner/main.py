# Level designer for The World

import click
from worlddesigner.load import load
from worlddesigner.new import new

CONTEXT_SETTINGS = {"help_option_names": ["-h", "--help"]}

@click.group(context_settings=CONTEXT_SETTINGS)
def main():
    """
    CLI tool for managing levels in The World.
    """
    pass

main.add_command(load)
main.add_command(new)

if __name__ == "__main__":
    main()
