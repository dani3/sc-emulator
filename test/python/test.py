"""Sanity test."""
from baldwin.target import Target

with Target() as target:
    target.reset()
