pkg_name = 'falcon-ms'
__version__ = '0.0.1'

try:
    from importlib.metadata import version, PackageNotFoundError

    try:
        __version__ = version(pkg_name)
    except PackageNotFoundError:
        pass
except ImportError:
    from pkg_resources import get_distribution, DistributionNotFound

    try:
        __version__ = get_distribution(pkg_name).version
    except DistributionNotFound:
        pass
