import click

from worlddesigner.editor import editor

@click.command()
@click.argument(
    "file",
    type=click.Path(exists=False, file_okay=True, dir_okay=False, writable=True, readable=True),
)
def new(file):
    """
    Create a new level FILE.
    """
    
    editor()
    pass