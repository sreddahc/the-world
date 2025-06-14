import click


@click.command()
@click.argument(
    "file",
    type=click.Path(exists=True, file_okay=True, dir_okay=False, writable=True, readable=True),
)
def load(file: str):
    """
    Load an existing level FILE.
    """
    print(file)
    pass