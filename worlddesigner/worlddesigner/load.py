import click

@click.command()
@click.argument(
    "file",
    type=click.Path(exists=True, file_okay=True, dir_okay=False, writable=True, readable=True),
)
def load(file):
    """
    Load a level FILE.
    """
    print("test")
    pass